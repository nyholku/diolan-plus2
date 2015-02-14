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

#include <string>
#include "encoder_usage.h"

using namespace std;

EncoderUsage::EncoderUsage()
{
	add(UsageDescriptor(
		ARG_HELP,
		"h",
		"help",
		UsageDescriptor::possible,
		"DEVICE",
		"Print this message.",
		UsageDescriptor::command
		));


	add(UsageDescriptor(
		ARG_CMD_ENCODE,
		"e",
		"encode",
		UsageDescriptor::required,
		"PASSWORD",
		string("Encode the input file with PASSWORD and save it to output file.")
		+ string("\n\tPASSWORD has to be provided as string of two hex digits per byte (like 01202040ac)."),
		UsageDescriptor::command
		));

	add(UsageDescriptor(
		ARG_CMD_DECODE,
		"d",
		"decode",
		UsageDescriptor::required,
		"PASSWORD",
		string("Decode the input file with PASSWORD and save it to output file.")
		+ string("\n\tPASSWORD has to be provided as string of two hex digits per byte (like 01202040ac)."),
		UsageDescriptor::command
		));
	add(UsageDescriptor(
		ARG_CMD_CONVERT,
		"c",
		"convert",
		UsageDescriptor::absent,
		"",
		"Convert the file from one format to enother.",
		UsageDescriptor::command
		));


	add(UsageDescriptor(
		ARG_INPUT_HEX,
		"ix",
		"input_hex",
		UsageDescriptor::required,
		"FILE_NAME",
		"Input file in Intel Hex Format.",
		UsageDescriptor::option
		));

	add(UsageDescriptor(
		ARG_INPUT_BIN,
		"ib",
		"input_bin",
		UsageDescriptor::required,
		"FILE_NAME",
		"Input file in Binary Format.",
		UsageDescriptor::option
		));

	add(UsageDescriptor(
		ARG_INPUT_DATA,
		"id",
		"input_data",
		UsageDescriptor::required,
		"DATA",
		string("Immediate mode - actual byte(s) specified in the command line")
		+ string("\n\tas string of two hex digits per byte (like 01202040ac)."),
		UsageDescriptor::option
		));

	add(UsageDescriptor(
		ARG_OUTPUT_HEX,
		"ox",
		"output_hex",
		UsageDescriptor::required,
		"FILE_NAME",
		"Output file in Intel Hex Format.",
		UsageDescriptor::option
		));

	add(UsageDescriptor(
		ARG_OUTPUT_BIN,
		"ob",
		"output_bin",
		UsageDescriptor::required,
		"FILE_NAME",
		"Output file in Binary Format.",
		UsageDescriptor::option
		));

}
