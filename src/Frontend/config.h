/*
	This file is part of Warzone 2100.
	Copyright (C) 2011  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef __SRC_CORE_CONFIG_LCONFIG_H__
#define __SRC_CORE_CONFIG_LCONFIG_H__

// TODO: Need a better place for this, the engine will need it.
enum GAMETYPE {
	GAMETYPE_CAMPAIGN,
	GAMETYPE_SINGLEPLAYER,
	GAMETYPE_MULTIPLAYER,
	GAMETYPE_MAX // Last!
};

void config_init();

#endif // __SRC_CORE_CONFIG_LCONFIG_H__
