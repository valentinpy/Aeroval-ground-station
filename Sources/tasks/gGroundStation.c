/*
 * Copyright (C) 2015 Valentin Py
 *
 * This file is part of Aeroval.
 *
 * Aeroval is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aeroval is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gGroungStation.h"
#include "../misc/def.h"
#include "../modules/mSwitches.h"
#include "../modules/mRS232.h"

void gGroundStation_Setup()
{
	//Configure UART, as it's used to transmit datas
	mRs232_Setup();

	return;
}

void gGroundStation_Run()
{
	UInt8 a1;
	UInt8 a2;

	//Should be handled in an interrupt
	if(mRs232_ReadDataFromBuffer(kUart3USB, &a1)==false) //Read from USB
	{
		mRs232_WriteChar(kUart4Aux, a1); //Send to UART4
	}
	if(mRs232_ReadDataFromBuffer(kUart4Aux, &a2)==false) //Read from UART 4
	{
		mRs232_WriteChar(kUart3USB, a2); //Send to USB
	}

	return;
}
