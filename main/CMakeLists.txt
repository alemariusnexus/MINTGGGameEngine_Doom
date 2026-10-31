# MINTGGGameEngine_Doom - A port of Doom to MINTGGGameEngine
# 
# Copyright (C) 2026 David Lerch
# SPDX-License-Identifier: GPL-3.0-or-later
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

include("${CMAKE_CURRENT_SOURCE_DIR}/../components/MINTGGGameEngine/cmake/MINTGGGameEngine.cmake")

MGG_ComponentPrologue()

set(SRCS
    main.cpp

    doomgeneric/doomgeneric/am_map.c
    doomgeneric/doomgeneric/d_event.c
    doomgeneric/doomgeneric/d_items.c
    doomgeneric/doomgeneric/d_iwad.c
    doomgeneric/doomgeneric/d_loop.c
    doomgeneric/doomgeneric/d_main.c
    doomgeneric/doomgeneric/d_mode.c
    doomgeneric/doomgeneric/d_net.c
    doomgeneric/doomgeneric/doomdef.c
    doomgeneric/doomgeneric/doomgeneric.c
    doomgeneric/doomgeneric/doomstat.c
    doomgeneric/doomgeneric/dstrings.c
    doomgeneric/doomgeneric/dummy.c
    doomgeneric/doomgeneric/f_finale.c
    doomgeneric/doomgeneric/f_wipe.c
    doomgeneric/doomgeneric/g_game.c
    #doomgeneric/doomgeneric/gusconf.c
    doomgeneric/doomgeneric/hu_lib.c
    doomgeneric/doomgeneric/hu_stuff.c
    #doomgeneric/doomgeneric/i_allegromusic.c
    #doomgeneric/doomgeneric/i_allegrosound.c
    doomgeneric/doomgeneric/i_cdmus.c
    doomgeneric/doomgeneric/i_endoom.c
    doomgeneric/doomgeneric/i_input.c
    doomgeneric/doomgeneric/i_joystick.c
    doomgeneric/doomgeneric/i_scale.c
    #doomgeneric/doomgeneric/i_sdlmusic.c
    #doomgeneric/doomgeneric/i_sdlsound.c
    doomgeneric/doomgeneric/i_sound.c
    doomgeneric/doomgeneric/i_system.c
    doomgeneric/doomgeneric/i_timer.c
    doomgeneric/doomgeneric/i_video.c
    doomgeneric/doomgeneric/icon.c
    doomgeneric/doomgeneric/info.c
    doomgeneric/doomgeneric/m_argv.c
    doomgeneric/doomgeneric/m_bbox.c
    doomgeneric/doomgeneric/m_cheat.c
    doomgeneric/doomgeneric/m_config.c
    doomgeneric/doomgeneric/m_controls.c
    doomgeneric/doomgeneric/m_fixed.c
    doomgeneric/doomgeneric/m_menu.c
    doomgeneric/doomgeneric/m_misc.c
    doomgeneric/doomgeneric/m_random.c
    doomgeneric/doomgeneric/memio.c
    doomgeneric/doomgeneric/mus2mid.c
    doomgeneric/doomgeneric/p_ceilng.c
    doomgeneric/doomgeneric/p_doors.c
    doomgeneric/doomgeneric/p_enemy.c
    doomgeneric/doomgeneric/p_floor.c
    doomgeneric/doomgeneric/p_inter.c
    doomgeneric/doomgeneric/p_lights.c
    doomgeneric/doomgeneric/p_map.c
    doomgeneric/doomgeneric/p_maputl.c
    doomgeneric/doomgeneric/p_mobj.c
    doomgeneric/doomgeneric/p_plats.c
    doomgeneric/doomgeneric/p_pspr.c
    doomgeneric/doomgeneric/p_saveg.c
    doomgeneric/doomgeneric/p_setup.c
    doomgeneric/doomgeneric/p_sight.c
    doomgeneric/doomgeneric/p_spec.c
    doomgeneric/doomgeneric/p_switch.c
    doomgeneric/doomgeneric/p_telept.c
    doomgeneric/doomgeneric/p_tick.c
    doomgeneric/doomgeneric/p_user.c
    doomgeneric/doomgeneric/r_bsp.c
    doomgeneric/doomgeneric/r_data.c
    doomgeneric/doomgeneric/r_draw.c
    doomgeneric/doomgeneric/r_main.c
    doomgeneric/doomgeneric/r_plane.c
    doomgeneric/doomgeneric/r_segs.c
    doomgeneric/doomgeneric/r_sky.c
    doomgeneric/doomgeneric/r_things.c
    doomgeneric/doomgeneric/s_sound.c
    doomgeneric/doomgeneric/sha1.c
    doomgeneric/doomgeneric/sounds.c
    doomgeneric/doomgeneric/st_lib.c
    doomgeneric/doomgeneric/st_stuff.c
    doomgeneric/doomgeneric/statdump.c
    doomgeneric/doomgeneric/tables.c
    doomgeneric/doomgeneric/v_video.c
    doomgeneric/doomgeneric/w_checksum.c
    doomgeneric/doomgeneric/w_file.c
    doomgeneric/doomgeneric/w_file_stdc.c
    doomgeneric/doomgeneric/w_main.c
    doomgeneric/doomgeneric/w_wad.c
    doomgeneric/doomgeneric/wi_stuff.c
    doomgeneric/doomgeneric/z_zone.c
    )

MGG_SetupApplication()

target_compile_options(${MGG_APP_MAIN_TARGET} PRIVATE
    -Wno-missing-field-initializers
    -Wno-unused-const-variable
    -Wno-format
    -Wno-unused-but-set-parameter
    -Wno-dangling-pointer
    #-Wno-unterminated-string-initialization
    -Wno-type-limits
    -Wno-implicit-fallthrough
    -Wno-unused-but-set-variable
    -Wno-unused-variable
    #-Wno-absolute-value
    -Wno-error
    )
