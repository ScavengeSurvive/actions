// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_actions
    #undef _inc_actions
#endif
// custom include-guard to ensure we don't duplicate
#if defined _actions_included
	#endinput
#endif
#define _actions_included

#include <a_samp>
#include <YSI\y_hooks>
#include <YSI\y_timers>
#include <velocity>
#include <tick-difference>

// called when the player surrenders, return 1 to cancel
forward OnPlayerSurrender(playerid);

// called when the player sits down, return 1 to cancel
forward OnPlayerSitDown(playerid);

// called when the player falls while jumping while handcuffed, return 1 to cancel
forward OnPlayerFallCuffed(playerid);

#define KEY_HOLD_TIME (800)
#define CUFF_JUMP_FALL_CHANCE (60)

static
		tick_CrouchKey[MAX_PLAYERS],
Timer:	timer_SitDown[MAX_PLAYERS];

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(IsPlayerInAnyVehicle(playerid)) {
		return Y_HOOKS_CONTINUE_RETURN_0;
	}

	// Sitting is only possible while not moving
	if(GetPlayerTotalVelocity(playerid) == 0.0) {
		if(newkeys == KEY_CROUCH) {
			new ret = CallLocalFunction("OnPlayerSitDown", "d", playerid);

			if(ret) {
				return Y_HOOKS_CONTINUE_RETURN_0;
			}

			tick_CrouchKey[playerid] = GetTickCount();
			timer_SitDown[playerid] = defer SitDown(playerid);

			return Y_HOOKS_CONTINUE_RETURN_0;
		}

		if(oldkeys == KEY_CROUCH) {
			if(GetTickCountDifference(GetTickCount(), tick_CrouchKey[playerid]) < KEY_HOLD_TIME) {
				stop timer_SitDown[playerid];
			}
			return Y_HOOKS_CONTINUE_RETURN_0;
		}

		if(newkeys & KEY_SPRINT && newkeys & KEY_CROUCH) {
			new ret = CallLocalFunction("OnPlayerSurrender", "d", playerid);

			if(ret) {
				return Y_HOOKS_CONTINUE_RETURN_0;
			}

			if(GetPlayerAnimationIndex(playerid) == 1381) {
				ClearAnimations(playerid);
			} else {
				ApplyAnimation(playerid, "ROB_BANK", "SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
			}

			return Y_HOOKS_CONTINUE_RETURN_0;
		}

		if(newkeys & KEY_CROUCH || newkeys & KEY_SPRINT || newkeys & KEY_JUMP) {
			if(GetPlayerAnimationIndex(playerid) == 43 || GetPlayerAnimationIndex(playerid) == 1497) {
				new ret = CallLocalFunction("OnPlayerFallCuffed", "d", playerid);

				if(ret) {
					return Y_HOOKS_CONTINUE_RETURN_0;
				}

				ApplyAnimation(playerid, "SUNBATHE", "PARKSIT_M_OUT", 4.0, 0, 0, 0, 0, 0);
			}
			return Y_HOOKS_CONTINUE_RETURN_0;
		}
	}

	// 60% chance to fall over if jumping while handcuffed
	if(newkeys & KEY_JUMP && !(oldkeys & KEY_JUMP) && GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED) {
		if(random(100) < CUFF_JUMP_FALL_CHANCE)
			ApplyAnimation(playerid, "GYMNASIUM", "gym_jog_falloff", 4.1, 0, 1, 1, 0, 0);
	}

	return Y_HOOKS_CONTINUE_RETURN_0;
}

timer SitDown[KEY_HOLD_TIME](playerid) {
	ApplyAnimation(playerid, "SUNBATHE", "PARKSIT_M_IN", 4.0, 0, 0, 0, 0, 0);
	defer SitLoop(playerid);
}

timer SitLoop[1900](playerid) {
	ApplyAnimation(playerid, "BEACH", "PARKSIT_M_LOOP", 4.0, 1, 0, 0, 0, 0);
}
