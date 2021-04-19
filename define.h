/*
 *
 *  Microsim (µsim) - small life simulation game
 *  Copyright (C) 2021 Elias Leitinger (eliasleiti@gmail.com)
 *
 *  usim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or any later version.
 *
 *  usim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */



/*
 *Definitions used for Creating the User interface and other thigns 
 *customize it to fit your terminal size. Making them smaller _will_
 *break things.
 *
 *XWORLD & YWORLD: Size of the World array
 *XBAR & YBAR: Set the size of the status bar
 *XSCREEN & YSCREEN: Combined size of World and bar
 *
 */
#define XWORLD 80
#define YWORLD 21
#define XBAR XWORLD
#define YBAR 3
#define XSCREEN XWORLD
#define YSCREEN YWORLD + YBAR


#define ESC 27
