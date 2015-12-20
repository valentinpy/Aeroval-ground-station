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
	char aDatas[kMonitoringStringLength];
	UInt8 i=0;


	//Get data from UART0 and send back to UART3 (USB)
	//That should be done using interrupts
	if(mSwitches_Get(kMaskSwitch0)==kMaskSwitch0)
	{
		//Read monitoring coming from Aeroval over Bluetooth

		//Wait for 0x0D
		mRs232_ReadDataFromBuffer(kUart0Aux, aDatas);
		if(*aDatas == 0x0D)
		{
			//Wait for next char
			while(mRs232_ReadDataFromBuffer(kUart0Aux, aDatas+1)==true);
			{
				//if char = 0X0A => we have a 0x0D, 0x0A
				if(*(aDatas+1)==0x0A)
				{
					//loop for the next string
					for (i=2; i<kMonitoringStringLength; i++)
					{
						while(mRs232_ReadDataFromBuffer(kUart0Aux, aDatas+i)==true);
					}

					//Send monitoring to PC over USB
					mRs232_WriteStringFixedSize(kUart3USB, aDatas, kMonitoringStringLength);
					mRs232_WriteStringFixedSize(kUart4Aux, aDatas, kMonitoringStringLength);
				}
			}
		}


	}
	return;
}
