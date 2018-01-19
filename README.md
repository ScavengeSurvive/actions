# Actions

Actions simply provides players with key prompts for animations.

* Player will surrender when the sprint and crouch keys are pressed simultaneously
* Player will sit down when the crouch key is held for 800ms
* Player may fall over if they attempt to jump while cuffed

## Installation

Simply install to your project:

```bash
sampctl package install ScavengeSurvive/actions
```

Include in your code and begin using the library:

```pawn
#include <actions>
```

## Usage

This library triggers the following events:

* `OnPlayerSurrender(playerid)`
  * called when the player surrenders, return 1 to cancel

* `OnPlayerSitDown(playerid)`
  * called when the player sits down, return 1 to cancel

* `OnPlayerFallCuffed(playerid)`
  * called when the player falls while jumping while handcuffed, return 1 to cancel

And can be configured using these definitions:

* `KEY_HOLD_TIME`
  * the time required to hold the crouch key to trigger the sit animation, default 800

* `CUFF_JUMP_FALL_CHANCE`
  * the percentage chance of a player failing to jump while cuffed, default 60

## Testing

To test, simply run the package:

```bash
sampctl package run
```

Then connect to `localhost:7777`.
