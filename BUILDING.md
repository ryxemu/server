# Building RyXEmu

Building binaries is optional and only needed if you want to build a custom distribution or want to contribute to the project. You can see [Releases](https://github.com/ryxemu/server/releases) otherwise to get built binaries.

## Get the Source

Clone the project from github:
```sh
git clone --recursive https://github.com/ryxemu/server.git
cd server
```

## Build for Windows

This is currently not supported.

## Build Linux with Docker

This is recommended if you don't plan to edit source code.

Assuming you're in a WSL instance or a bash prompt for windows/linux, and have docker installed, you can run the following command:
```
make docker-build
```
This will create a `build` subfolder and compile all binaries to `build/bin` using the ubuntu 22.04 image found in `.devcontainer/Docker.ubuntu.dev`

## Build Within a Dev Container

This is recommended if you plan to edit source code.

If you open the folder in vscode, you may get a notification asking if you'd like to reopen it in a dev container. If you do not, you can click the bottom left area of vscode and look for either the option to `Reopen in Container``, or `Install Dev Container Extension``. If the install option is available, install it and then Reopen in Container.

Once open in a dev container, you will get intellisense, and a suite of extensions that allow you to work on the source code. You can press the `build` text located at the bottom bar of vscode to build the source code.

## Build Baremetal

This is not recommended.

If you'd like to build the binaries natively inside linux without docker, you can use the .devonctainer subfolder for inspiration of what packages are required. `Each Dockerfile.<name>.dev` folder will list the packages known to be needed for a dev environment. Also, the `devcontainer.json` contains extensions that you may want to consider installing. Once done, you should be able to run the build command similar to the dev container final steps.

## Advanced Building for Other Linux Distributions

If you'd like to build for another distribution, you can see a list inside the .devcontainer folder in the pattern of `Dockerfile.<distroname>.dev`. Taking a distroname, for example alpine, you can use the Docker build process above, instead changing it to `make docker-build-alpine`, replacing alpine with the distribution you prefer.

A new folder called `build-alpine` will appear, and your binaries will be built inside the bin subfolder.

If you don't see a distribution you'd like your binaries built for, feel free to PR your own or ask in discord for it's support.