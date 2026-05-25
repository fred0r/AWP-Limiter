#if defined _awp_limiter_n
    #endinput
#endif
#define _awp_limiter_n

#pragma semicolon 1

/**
 * Indicates how a player tried to acquire an AWP.
 */
enum AwpGiveType:GIVE_TYPE
{
    BUY,
    TOUCH,
    OTHER   // Given by a 3rd-party plugin
};

/**
 * Indicates why an AWP was restricted or taken.
 */
enum AwpRestrictionType:RESTRICTION_TYPE
{
    AWP_ALLOWED,            // AWP is allowed (no restriction)
    LOW_ONLINE,             // Not enough players online
    TOO_MANY_AWP_ON_TEAM,   // Team has reached its AWP limit
    ROUNDS_PAUSE,           // Player is in a cooldown after dying with AWP
    LEADING_TEAM            // Player's team is leading in overall round score
};

/**
 * Return values for forwards.
 */
enum
{
    AWPL_CONTINUE,  // Let default behavior proceed
    AWPL_BREAK      // Override default behavior
};

/**
 * Called before low online mode is activated.
 *
 * @return              AWPL_CONTINUE to proceed with activating low online mode
 *                      AWPL_BREAK to prevent low online mode from starting
 */
forward awpl_low_online_start();

/**
 * Called before low online mode is deactivated.
 *
 * @return              AWPL_CONTINUE to proceed with deactivating low online mode
 *                      AWPL_BREAK to keep low online mode active
 */
forward awpl_low_online_stop();

/**
 * Called every time a player tries to acquire an AWP and is blocked.
 *
 * @param id            Player index
 * @param iGiveType     How the AWP was acquired (BUY, TOUCH, OTHER)
 * @param iRestrictType Why the AWP is being restricted (see RESTRICTION_TYPE enum)
 *
 * @return              AWPL_CONTINUE to allow the AWP to be blocked
 *                      AWPL_BREAK to allow the player to take the AWP despite restrictions
 */
forward awpl_player_tried_to_get_awp(const id, AwpGiveType:iGiveType, AwpRestrictionType:iRestrictType);

/**
 * Called every time an AWP is about to be removed from a player.
 *
 * @param id            Player index
 * @param iRestrictType Reason for removal: LOW_ONLINE, TOO_MANY_AWP_ON_TEAM, or LEADING_TEAM
 *
 * @return              AWPL_CONTINUE to allow the AWP to be taken by the plugin
 *                      AWPL_BREAK to prevent the AWP from being removed
 */
forward awpl_awp_taken_from_player(const id, AwpRestrictionType:iRestrictType);

/**
 * Called when a player receives compensation for a confiscated AWP.
 *
 * @note This forward is only called when "awpl_give_compensation" is not 0.
 * @note Return AWPL_BREAK to provide your own compensation instead.
 *
 * @param id            Player index
 *
 * @return              AWPL_CONTINUE to use the default compensation
 *                      AWPL_BREAK to prevent default compensation
 */
forward awpl_give_compensation(const id);

/**
 * Called once on map start to decide whether the plugin should run on this map.
 *
 * @note This forward is called during plugin_init(), before the plugin
 *       has fully initialized. Automatic AWP-map detection still applies.
 *
 * @param szMapName     Current map name
 *
 * @return              AWPL_CONTINUE to let the plugin run on this map
 *                      AWPL_BREAK to disable the plugin for this map
 */
forward awpl_plugin_should_work_on_this_map(const szMapName[]);

/**
 * Checks if the low online mode is currently active.
 *
 * @return              True if the low online mode is currently active, false otherwise.
 */
native bool:awpl_is_low_online();

/**
 * Force start or stop low online mode.
 *
 * @note The mode set by this native remains active only
 *       until the next online check.
 * @note Setting bSet to true will immediately confiscate all AWPs.
 *
 * @param bSet          True to activate low online mode, false to deactivate it
 *
 * @noreturn
 */
native awpl_set_low_online(bool:bSet);

/**
 * Checks if players in given team can take AWP.
 *
 * @param iTeam         Team index
 *
 * @return              True if players in given team can take AWP, false otherwise.
 */
native bool:awpl_can_team_take_awp(TeamName:iTeam);

/**
 * Checks if a given player can take an AWP.
 *
 * @param id            Player index
 * @param iReason       The optional variable to store the reason if player can't take AWP.
 *                      Look at the enum RESTRICTION_TYPE
 *
 * @return              True if player can take AWP, false otherwise.
 */
native bool:awpl_can_player_take_awp(id, &AwpRestrictionType:iReason = AWP_ALLOWED);
