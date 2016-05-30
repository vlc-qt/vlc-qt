# How to contribute to VLC-Qt

## Feature Requests

It is a high possibility that we did not include all libVLC features into
the library. Feel free to open an issue describing your needed functionality.
Widgets and QML related ideas are also accepted.

If you can, you are encouraged to write the new features by yourself and submit
a pull request (more details below).

Please do not send send feature requests and bug reports via e-mail!


## Submitting Issues

Found a bug in VLC-Qt? Here are some guidelines on how to report the issue so
it can be resolved it as fast as possible:

- Explain in detail how to reproduce the issue.
- Include sample code you used, build output and other **relevant** information.
- Please include information on what VLC, Qt, VLC-Qt version you are using
  and what operating system you are running.

Your issue will be closed when not replied for a month or longer. Feel free to reopen it later if still encountering the problem.


## Writing guides

You can write guides [here](http://discuss.tano.si). Classic markdown and code
formatting is supported. For full examples, open pull request on the
[examples repository](https://github.com/vlc-qt/examples).


## Pull Requests

To ease the pull request merge into mainline, please follow these requirements:

- The pull request title and message should be meaningful enough that reading
  the code is not necessary.
- VLC 2.1 is still supported and VLC-Qt must build against it. Wrap libVLC functions
  from version newer than 2.1 in compiler if clauses to maintain backwards
  compatibility. Version should be defined as a base 16 integer (similar to Qt).

  ```
  #if LIBVLC_VERSION >= 0x020200
      _vlcEqualizer = new VlcEqualizer(this);
  #endif
  ```
- Use similar coding style as you see in existing code, notably:

  - use provided clang-format config (mostly based on LLVM coding style)
  - use 4 spaces indentation not tabs
  - private variables have underscore as a prefix ```_vlcInstance```
  - all public functions should be documented, for better readability put each
    argument in a new line (doxygen commands are escaped in this documentation)
```
/*!
    \\brief Sets the application name.

    libvlc passes this as the user agent string when a protocol requires it.

    \\param application Application name (QString)
    \\param version Application version (QString)
*/
void setUserAgent(const QString &application,
                  const QString &version);
```

- **One pull request per feature**. If you want to do more than one thing, send
  multiple pull requests. You should create a separate branch for each one.
- Make sure each individual commit in your pull request is meaningful.
  If you had to make multiple intermediate commits while developing, please
  squash them before sending them to us.
- Use git's [interactive rebase](https://help.github.com/articles/interactive-rebase)
feature to tidy up your commits before submitting the pull request.
- Tests needs to be written for new features. Code coverage should never decrease.
- Your PRs must pass build tests on Travis and AppVeyor. We can assist you
  with support for other platforms that you work on, so please note where you
  tested the code before submitting the PR.
