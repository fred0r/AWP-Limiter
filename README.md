# AWP-Limiter

The plugin allows restricting AWP usage during low player counts, as well as limiting the number of AWPs per team.

Online player count is recalculated each new round, allowing the current round to finish under the same conditions it started.

## Features

- Ability to set the minimum number of players required for AWPs to become available.
- Option to exclude spectators from the online player count.
- Automatic plugin deactivation on AWP maps, including those without the "awp_" prefix (e.g. "css_india").
- CSDM support: the plugin supports infinite rounds, checking online counts at configurable intervals or on every player spawn instead of each round.
- Compensation for confiscated AWPs in the form of a rifle or money.
- Two team AWP limit modes:
  1. Fixed limit per team.
  2. Dynamic limit as a percentage of online players. Example: 10% — 10 players = 1 AWP per team, 20 = 2, 30 = 3.
- Message to all players when AWPs become available again (toggleable).
- Option to exclude bots from online player counts and AWP tracking.
- Restrict AWP for the team leading in overall round score (`awpl_winner_no_awp`).
- Built-in debug mode with detailed logs for quick and easy issue identification.
- Well-optimized plugin.

## Configuration

The config file `AWPLimiter.cfg` is generated automatically in `amxmodx/configs/` on first plugin start. All cvars and their default values are written into it.

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
