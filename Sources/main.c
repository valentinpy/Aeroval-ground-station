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

#include "misc/derivative.h"
#include "misc/def.h"

#include "modules/mCpu.h"
#include "modules/mLeds.h"
#include "modules/mDelay.h"
#include "modules/mGpio.h"
#include "modules/mSwitches.h"

#include "tasks/gGroungStation.h"

void main(void)
{
	//Non specific modules initialization
	mCpu_Setup();
	mDelay_Setup();
	mLeds_Setup();
	mGpio_Setup();
	mSwitches_Setup();

	//Tasks initialization
	gGroundStation_Setup();

	//Wait 1second after setup
	UInt16 aDelayMain = mDelay_GetDelay(kPit0, 1000);
	while(mDelay_IsDelayDone(kPit0, aDelayMain)==false);

	//Indicate that programm is ready.
	mLeds_AllOn();

	//Main loop
	while(1)
	{

		gGroundStation_Run();

		//Breath if alive :)
		if(mDelay_IsDelayDone(kPit0, aDelayMain)==true)
		{
			mDelay_ReStart(kPit0, aDelayMain, 500);
			mLeds_AllToggle();
		}
	}

	//Never happens (infinite loop above)
	return;
}
