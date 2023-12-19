## RyXEmu

This is a massive overhaul of eqmacemu to support a newer EQ Client. 

Currently, work is being done to target Laurian's Song December 12th, 2023 client. This is subject to change.

A stretch goal is to support the latest client (or a number of recently released clients).

Features also added include that are unique to EQMacEmu/EQEMU:

- [x] Overhaul of Quest API functions, including removal of luabind for sol2
- [ ] Revamp lua mod system to be first class supported
- [ ] Overhaul of SQL Tables
- [x] Clean up eqemu_config to a simpler config.yaml
- [ ] Move all zone/world APIs to use gRPC/protobuf, with a proxy server for RESTful
- [ ] Support Advanced loot (with option to force disable it server side)
- [ ] Support Fellowships
- [ ] Support large bags
- [x] Remove support of titanium/RoF2
- [ ] Remove support of takp client
- [ ] Oauth Token Login (live-like)
