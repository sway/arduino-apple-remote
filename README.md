# Apple Remote library for Arduino

This library can work with an IR Receiver and an IR LED to decode and emit
[Apple Remote][1] IR codes.

The IR led is expected to be wired to the Arduino's pin #3 and GND.

The IR receiver is expected to be wired to the Arduino's pin #2, GND and 5V.

## Code example

Emitting signals.

```c
#include <apple-remote.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("Point your IR led to an AppleTV.");
}

void loop()
{
  // This is like pressing the real "menu" button.
  Serial.println("Sending signal: menu.");
  apple_remote_menu();
  delay(100000);
}
```

Receiving signals

```c
#include <apple-remote.h>
#define SIGNAL_MAX_LENGTH 70

void setup()
{
  Serial.begin(9600);
  Serial.println("Point your Apple Controller to your IR sensor.");
}

void loop()
{
  unsigned int signal[SIGNAL_MAX_LENGTH];
  bool captured;
  int code;

  captured = irdebug_capture_signal(signal, SIGNAL_MAX_LENGTH);

  if (captured) {
    irdebug_print_signal(signal);
    code = apple_remote_match(signal);

    switch (code) {
      case APPLE_REMOTE_MENU:
        Serial.println("[menu]");
        break;
      case APPLE_REMOTE_RIGHT:
        Serial.println("[right]");
        break;
      case APPLE_REMOTE_LEFT:
        Serial.println("[left]");
        break;
      case APPLE_REMOTE_UP:
        Serial.println("[up]");
        break;
      case APPLE_REMOTE_DOWN:
        Serial.println("[down]");
        break;
      case APPLE_REMOTE_PLAY:
        Serial.println("[play]");
        break;
      case APPLE_REMOTE_CENTER:
        Serial.println("[center]");
        break;
      case APPLE_REMOTE_REPEAT:
        Serial.println("[repeat]");
        break;
      default:
        Serial.println("[?]");
    }
  }
}
```

If the above code does does not work or you see things like:

```
[?]
[?]
[?]
[?]
```

instead of button reads, you should try changing the expected Apple Remote ID:

## Changing the Apple Remote's model

This library covers two Apple Remote models, these two models have been tested
with the aluminium controller only.

If you need to switch between controller models a small hack is required. Open
`lib/apple-remote/apple-remote.h` with your favorite text editor and locate the
`APPLE_REMOTE_MODEL` constant, the line should look like this:

```
#define APPLE_REMOTE_MODEL 0xc7
```

change the `0xc7` number for `0xcf`. Clean the project, recompile and try
again.

## How to install

1. Install the [irdebug.h][2] library.
2. Copy the `lib/apple-remote/` directory to your Arduino's library path, for
	 example: `sudo cp -r lib/apple-remote /usr/share/arduino/libraries/`.
3. Include the `apple-remote.h` file into your main Arduino code, for example
	 `#include <apple-remote.h>`.

## License

> Copyright (c) 2014 José Carlos Nieto, https://menteslibres.net/xiam
>
> Permission is hereby granted, free of charge, to any person obtaining
> a copy of this software and associated documentation files (the
> "Software"), to deal in the Software without restriction, including
> without limitation the rights to use, copy, modify, merge, publish,
> distribute, sublicense, and/or sell copies of the Software, and to
> permit persons to whom the Software is furnished to do so, subject to
> the following conditions:
>
> The above copyright notice and this permission notice shall be
> included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
> EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
> MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
> NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
> LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
> OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
> WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

[1]: http://en.wikipedia.org/wiki/Apple_Remote
[2]: https://github.com/xiam/arduino-irdebug
