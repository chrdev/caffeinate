# Caffeinate & Monitor-Off

These two utilites work on Windows.

Caffeinate prevents the system from sleeping, which helps run a prolonged 
job whithout tangling the system power settings. It also optionally turns
off the display.

Monitor-off turns off the display immediately.

### Usage

```
caffeinate
  /D, /M  Don't turn off monitor.
  /?      Show help.
```

monitor-off has no parameters. Simply run it.

### Compile

Use Pelles C Command Prompt, run build-x64.cmd or build-x32.cmd

### Update history

Ver 1.0.1 Feb, 2023

Fix wait for input behavior.
Improve prompts.

### License 0BSD

BSD Zero Clause License

Copyright (c) [2023] [chrdev]

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
