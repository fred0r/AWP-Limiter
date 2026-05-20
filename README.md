# AWP-Limiter

The plugin allows restricting AWP usage during low player counts, as well as limiting the number of AWPs per team.

Online player count is recalculated each new round, allowing the current round to finish under the same conditions it started.

## Dependencies

- **AMX Mod X** 1.9+
- **ReAPI** (ReGameDLL)

## Installation

1. Compile `scripting/awp_limiter.sma` and place the `.amxx` file in `amxmodx/plugins/`.
2. (Optional) Compile `scripting/awp_limiter_disabled_maps.sma` and place the `.amxx` file in `amxmodx/plugins/`. Copy `configs/awp_limiter_disabled_maps.ini` to `amxmodx/configs/`.
3. Place `data/lang/awp_limiter_n.txt` in `amxmodx/data/lang/`.
4. Add plugin names to `amxmodx/configs/plugins.ini`.
5. Restart the server or change the map.

The config file `AWPLimiter.cfg` is generated automatically in `amxmodx/configs/` on first plugin start.

## Features

- Ability to set the minimum number of players required for AWPs to become available.
- Option to exclude spectators from the online player count.
- Automatic plugin deactivation on AWP maps, including those without the `awp_` prefix (via sub-plugin).
- CSDM support: the plugin supports infinite rounds, checking online counts at configurable intervals or on every player spawn instead of each round.
- Compensation for confiscated AWPs in the form of a rifle or money.
- Two team AWP limit modes:
  1. Fixed limit per team.
  2. Dynamic limit as a percentage of online players. Example: 10% — 10 players = 1 AWP per team, 20 = 2, 30 = 3.
- Message to all players when AWPs become available again (toggleable).
- Option to exclude bots from online player counts and AWP tracking.
- Cooldown system: force players who die with an AWP to wait N rounds before taking another (persists across disconnects by SteamID).
- Restrict AWP for the team leading in overall round score (`awpl_winner_no_awp`). Also strips AWP from alive players who switch to the leading team.
- Built-in debug mode with detailed logs for quick and easy issue identification. Enabled by compiling with `AMX_FLAG_DEBUG`. Logs are written to `amxmodx/logs/awpl_debug/`.

## Configuration

| Cvar | Default | Description |
|------|---------|-------------|
| `awpl_chat_prefix` | `^3[^4AWP^3]` | Plugin chat prefix |
| `awpl_min_players` | `10` | Minimum players required for AWPs to become available |
| `awpl_limit_type` | `1` | AWP limit type: `1` — exact number per team, `2` — percentage of online players |
| `awpl_max_awp` | `2` | Maximum AWPs per team (used when `awpl_limit_type` is `1`) |
| `awpl_percent_players` | `10` | Percentage of online players for calculation (used when `awpl_limit_type` is `2`) |
| `awpl_immunity_flag` | `a` | Immunity flag (leave blank to disable) |
| `awpl_skip_bots` | `0` | Skip tracking bots: `0` — disabled, `1` — enabled |
| `awpl_skip_spectators` | `1` | Skip spectators in online count: `0` — disabled, `1` — enabled |
| `awpl_message_allow_awp` | `1` | Notify all players when AWP becomes available: `0` — disabled, `1` — enabled |
| `awpl_round_infinite` | `0` | Infinite round support (CSDM): `0` — disabled, `>=1` — check online every N seconds, `-1` — check on every player spawn |
| `awpl_give_compensation` | `-1` | Compensation for confiscated AWP: `-1` — rifle (AK-47 or M4A1), `0` — disabled, `>=1` — amount of money |
| `awpl_rounds_pause_num` | `0` | Rounds a player must wait before taking AWP again after dying with one. `0` — disabled |
| `awpl_winner_no_awp` | `0` | Restrict AWP for the team leading in overall round score: `0` — disabled, `1` — enabled |
| `AWPLimiter_version` | auto | Plugin version (read-only) |

## Disabled Maps (Sub-Plugin)

The optional sub-plugin `awp_limiter_disabled_maps.amxx` allows disabling AWP Limiter on specific maps that don't have the `awp_` prefix (e.g. `aim_headshot`).

Add map names to `configs/awp_limiter_disabled_maps.ini` — one per line. The sub-plugin uses the `awpl_plugin_should_work_on_this_map` forward.

## Language Support

The plugin includes translations for: English, Russian, Ukrainian, Romanian, German, Chinese.

Language keys are in `data/lang/awp_limiter_n.txt`.

## API (For Developers)

Third-party plugins can interact with AWP Limiter through forwards and natives.

### Forwards

| Forward | Description | Return |
|---------|-------------|--------|
| `awpl_low_online_start()` | Before low online mode activates | `AWPL_BREAK` to prevent |
| `awpl_low_online_stop()` | Before low online mode deactivates | `AWPL_BREAK` to keep active |
| `awpl_player_tried_to_get_awp(id, GIVE_TYPE, RESTRICTION_TYPE)` | When a player attempts to acquire AWP | `AWPL_BREAK` to allow AWP |
| `awpl_awp_taken_from_player(id, RESTRICTION_TYPE)` | Before removing AWP from a player | `AWPL_BREAK` to prevent removal |
| `awpl_give_compensation(id)` | Before giving compensation | `AWPL_BREAK` to prevent default compensation |
| `awpl_plugin_should_work_on_this_map(szMapName[])` | On map start to decide if plugin should run | `AWPL_BREAK` to disable plugin |

### Natives

| Native | Description |
|--------|-------------|
| `awpl_is_low_online()` | Returns `true` if low online mode is active |
| `awpl_set_low_online(bool)` | Force-start or force-stop low online mode (lasts until next check) |
| `awpl_can_team_take_awp(TeamName)` | Returns `true` if the given team has room for another AWP |
| `awpl_can_player_take_awp(id, &reason)` | Returns `true` if the given player can take AWP; sets `reason` if not |

### Enums

`GIVE_TYPE`: `BUY`, `TOUCH`, `OTHER`

`RESTRICTION_TYPE`: `AWP_ALLOWED`, `LOW_ONLINE`, `TOO_MANY_AWP_ON_TEAM`, `ROUNDS_PAUSE`, `LEADING_TEAM`

Return values: `AWPL_CONTINUE` (let default behavior proceed), `AWPL_BREAK` (override default behavior).

Include `awp_limiter_n.inc` in your plugin to use these.
