# wav-editor

Command line WAV viewer and editor (inspired by previous project [midi-editor](https://github.com/rmtsukuru/midi-editor).

## Usage

Build by running `make`. This will generate `wav.exe` (should be `wav` on UNIX-based systems).

Run `./wav.exe filename.wav --hex` to load and display contents of filename.wav.

Piping to `less` or using output redirection (`>`) to a file is recommended because the file contents tend to be long even for the simplest of WAV files.

Run `/.wav.exe filename.wav --write` to create a new WAV file called filaname.wav.

More details TBD, WAV editing features are in progress.

