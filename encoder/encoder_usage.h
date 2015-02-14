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

#ifndef FU_USAGE_H_INCLUDED
#define FU_USAGE_H_INCLUDED

#include "osdep/osdep.h"

#include "parser/usage.h"

const unsigned int ARG_HELP = 1;
const unsigned int ARG_CMD_ENCODE = 2;
const unsigned int ARG_CMD_DECODE = 3;
const unsigned int ARG_CMD_CONVERT = 4;
const unsigned int ARG_INPUT_HEX = 5;
const unsigned int ARG_INPUT_BIN = 6;
const unsigned int ARG_INPUT_DATA = 7;
const unsigned int ARG_OUTPUT_HEX = 8;
const unsigned int ARG_OUTPUT_BIN = 9;

class EncoderUsage: public Usage
{
public:
	EncoderUsage();
};


#endif // FU_USAGE_H_INCLUDED
