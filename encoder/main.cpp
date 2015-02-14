/***************************************************************************
 *   Copyright (C) 2007 by Diolan                                          *
 *   www.diolan.com                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "osdep/osdep.h"

#include "encoder.h"
#include "parser/parser.h"
#include "parser/parameters.h"
#include "encoder_usage.h"
#include "image/argumentimage.h"
#include "image/binimage.h"
#include "image/intel_hex_image.h"
#include "image/cout_image.h"
#include "exception/exception.h"
#include "encoder_buffer.h"
#include <string.h>

Image* createInputImage(const Parameters& params)
{
	if (params.contain(ARG_INPUT_BIN))
		return new BinImage(params[ARG_INPUT_BIN].value());
	if (params.contain(ARG_INPUT_DATA))
		return new ArgumentImage(ARG_INPUT_DATA, params);
	if (params.contain(ARG_INPUT_HEX))
		return new IntelHexImage(params[ARG_INPUT_HEX].value());

	throw DEImageAbsent();
//	return new CoutImage();

}

Image* createOutputImage(const Parameters& params)
{
	if (params.contain(ARG_OUTPUT_BIN))
		return new BinImage(params[ARG_OUTPUT_BIN].value());
	if (params.contain(ARG_OUTPUT_HEX))
		return new IntelHexImage(params[ARG_OUTPUT_HEX].value());

	return new CoutImage();

}

void save(FragBuffer *buffer, const Parameters& params)
{
	Image *image = NULL;
	try
	{
		image = createOutputImage(params);
		image->open(false);
		const size_t dataSize = 0x100;
		unsigned char data[dataSize];
		size_t size, address;

		FragBuffer::iterator it = buffer->begin();
		while (it != buffer->end())
		{
			address = buffer->address(it);
			size = buffer->read(data, dataSize, address);
// 			printf("%08X : %08X\n", address, size);
			image->setWriteAddress(address);
			image->write(data, size);
			it = buffer->lower_bound(address + dataSize);
		}

		image->close();
		delete image;
		image = NULL;
	}
	catch(...)
	{
		if (image != NULL)
			delete image;
		throw;
	}

}

void load(FragBuffer* buffer, const Parameters& params, size_t *start, size_t *end)
{
	Image *image = NULL;
	const size_t dataSize = 0x100;
	unsigned char data[dataSize];
	*start = 0xFFFFFFFF;
	*end = 0x0;

	try
	{
		image = createInputImage(params);
		image->open(true);
		buffer->clear();

		size_t size, address;
		while (0 != (size = image->read(data, dataSize, &address)))
		{
// 			printf("%08X : %08X\n", address, size);
			buffer->write(data, size, address);
			if (*end < address+size)
				*end = address+size;
			if (*start > address)
				*start = address;
		}
		image->close();
		delete image;
	}
	catch(...)
	{
		if (image != NULL)
			delete image;
		throw;
	}
}

void getKey(const Parameters& params, const unsigned int argument, XTEA_KEY_T key[4])
{
	Image * image;
	size_t address, size;
	try
	{
		image = new ArgumentImage(argument, params);
		image->open(true);
		if (image->getSize() != 16)
			throw DEBadArgument(params[argument].argument());
		size = image->read((unsigned char*)key, 16, &address);
		if (size != 16)
			throw DEBadArgument(params[argument].argument());
		image->close();
		delete image;
	}
	catch(...)
	{
		delete image;
		throw;
	}
}

int main (int argc, char *argv[])
{

	/*
	cout << "HELLO!\n";

	EncoderBuffer eb;
		XTEA_KEY_T key[4];
		XTEA_KEY_T data[2];
		memcpy(&key[0],(void*)"0123456789ABCDEF",16);
		memcpy(&data[0],(void*)"DEADBEEF",8);
		cout << "encode!\n";
		eb.decode(key,data);
		return(0);
	*/

	try
	{
		EncoderUsage usage;
		Parser parser(usage);
		Parameters params(usage);
		parser.parse(argc, argv, &params);
		if (params.contain(ARG_HELP))
		{
			cout << "USAGE:\n";
			cout << "encoder <COMMAND> [OPTIONS...]\n";
			usage.print();
			return 0;
		}

		EncoderBuffer buffer;
		size_t begin, end;
		load(&buffer, params, &begin, &end);
		XTEA_KEY_T key[4];
		unsigned int command = params.command();
		switch(command)
		{
		case ARG_CMD_ENCODE:
			getKey(params, ARG_CMD_ENCODE, key);
			buffer.encode(key);
			break;
		case ARG_CMD_DECODE:
			getKey(params, ARG_CMD_DECODE, key);
			buffer.decode(key);
			break;
		case ARG_CMD_CONVERT:
			break;
		default:
			throw DEBadArgument(params[command].argument());
		}

		save(&buffer, params);
	}
	catch(DException &err)
	{
		cout << err.getErrMessage() << endl;
		cout << "Operation aborted.\n";
		return -1;
	}
	catch (...)
	{
		return -1;
	}



}
