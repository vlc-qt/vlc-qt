# VLC-Qt Library

## Important changes with 1.0

**Since 1.0 release, libraries were renamed and includes prefix changed
to make them fully modular. Please, update CMake search scripts, configure
scripts and/or makefiles before updating to latest version.**


## Examples and guides
VLC-Qt examples are now located in the [examples](https://github.com/vlc-qt/examples)
repository.

All discussions that are not bug related can be made [here](https://discuss.tano.si).
This is also a place where you can publish your guides.


## Requirements

VLC-Qt can be built with any common compiler (g++, clang, MSVC, MinGW).
Build files are generated using [CMake](http://www.cmake.org) (3.0.2 or later).

All stable versions of VLC since 2.0 work with VLC-Qt.
Both Qt version 4 (4.8 or later) and 5 (5.2 or later) are supported but
can not be used at the same time. Binaries will always be provided for latest
Qt version released at the time of release. Note that Qt4 may require some
manual intervention when installing.


## Building
See [How to build VLC-QT](md_building.html).


## Submitting Issues

Found a bug in VLC-Qt? Here are some guidelines on how to report the issue so
it can be resolved it as fast as possible:

- Explain in detail how to reproduce the issue.
- Include sample code you used, build output and other **relevant** information.
- Please include information on what VLC, Qt, VLC-Qt version you are using
  and what operating system you are running.

Your issue will be closed when not replied for a month or longer. Feel free to
reopen it later if still encountering the problem.

Please do not send send feature requests and bug reports via e-mail!


## Pull Requests

To ease the pull request merge into mainline, please follow these requirements:

- The pull request title and message should be meaningful enough that reading
  the code is not necessary.
- VLC 2.0 is still supported and VLC-Qt must build against it. Wrap libVLC
  functions from version newer than 2.0 in compiler if clauses to maintain
  backwards compatibility. Version should be defined as a base 16 integer
  (similar to Qt).
  ```
  #if LIBVLC_VERSION >= 0x020200
      _vlcEqualizer = new VlcEqualizer(this);
  #endif
  ```
- Use similar coding style as you see in existing code, notably:
  - use 4 spaces indentation not tabs
  - private variables have underscore as a prefix ```_vlcInstance```
  - all public functions should be documented, for better readability put each
    argument in a new line
- **One pull request per feature**. If you want to do more than one thing, send
  multiple pull requests. You should create a separate branch for each one.
- Make sure each individual commit in your pull request is meaningful.
  If you had to make multiple intermediate commits while developing, please
  squash them before sending them to us.
- Use git's [interactive rebase](https://help.github.com/articles/interactive-rebase)
feature to tidy up your commits before submitting the pull request.
- Your PRs must pass build tests on Travis and AppVeyor. We can assist you
  with support for other platforms that you work on, so please note where you
  tested the code before submitting the PR.
