# x-copilot

[![Build Status](https://travis-ci.org/owentar/x-copilot.svg?branch=master)](https://travis-ci.org/owentar/x-copilot)

This is a plugin for [X-Plane] to support voice commands in the simulator. The main intention is to have a
cross-platform plugin (Win, Mac and Linux) which allows the user to instruct voice commands to the simulator.

## Table of contents
- [Goals](#goals)
- [Commands](#commands)
- [Contribute](#contribute)
- [Development](#development)
  - [How it works](#how-it-works)
  - [Structure](#structure)

## Goals
The X-Plane community is quite big and collaborative, this plugin will relay heavily on the community
to extend the supported commands as well as improving the voice recognition.

Main objectives during development:
- Commands should be easy to configure and extend through a configuration file
- Voice recognition should be easy to improve / train

## Commands
The commands are recognized using [regular expressions](https://www.regular-expressions.info/) defined in the file:
`config/default-commands.json`.

This JSON file specify an array containing the metadata for each supported command. This metadata should have the
following structure:

| Property | Required | Description                                                                 |
|----------|:--------:|-----------------------------------------------------------------------------|
| regex    |    yes   | valid regular expression to recognize the command                           |
| type     |    yes   | data type of the data-ref value                                             |
| dataRefs |    yes   | array containing the data-refs id's to update for the corresponding command |

## Contribute
Want to help? Great! All contribution are welcomed. There are many ways to contribute:
- Issues: raising, diagnosing and helping to investigate them
- Commands: adding more commands to the config files (default commands or specific per airplane)
- Speech recognition: there is a lot of room for improvement in the speech recognition, from training the library to find better ways to configure it to make it more accurate.

Any input is already a contribution, feel free to [create an issue](https://github.com/owentar/x-copilot/issues/new) and write it down so we can all work on it.

## Development
We're using [CMake] to generate the corresponding scripts to build the plugin in the different
platforms.

Most of the dependencies will be uploaded to the repository if possible, others will have to be installed manually
by the developer.
- [X-Plane SDK] (binaries uploaded in the this repo)
- [Portaudio] (binaries uploaded in the this repo)
- [Pocketsphinx] (binaries uploaded in the this repo)
- [Sphinx] (binaries uploaded in the this repo)
- [Boost] v1.69 **(manually installed by the developer)**

### How it works
The process is quite simple:

1. Transcribe voice commands to text using [Pocketsphinx] project.
2. When the command is in a string format, it's parsed through a regular expression to identify and extract the data from it
3. Once the command is recognized, it's translated to data ref operations (setting / getting one or more data refs in x-plane)

### Structure
The project contains three subprojects:
- **src** contains the source code of the plugin
- **test** contains all the unit / integration tests (using [Google Test] and [Google Mock])
- **demo** a simple console application to smoke test the full integration (except the X-Plane SDK)

It also contains some resources folders:
- **config** contains all the configurations files for the commands
- **pocketsphinx-data** contains all the necessary files for the speech recognition library (acoustic model, dictionary and language model)


[CMake]: https://cmake.org/
[X-Plane]: http://www.x-plane.com/
[X-Plane SDK]: http://www.xsquawkbox.net/xpsdk/mediawiki/Main_Page
[Portaudio]: http://www.portaudio.com/
[Pocketsphinx]: https://github.com/cmusphinx/pocketsphinx
[Sphinx]: https://cmusphinx.github.io/
[Boost]: http://www.boost.org/
[Google Test]: https://github.com/google/googletest
[Google Mock]: https://github.com/google/googlemock
