All packets are zero byte padded for formatting reasons and also to ensure
that we can grab the start out of the middle of a stream.

Packets to which we expect an error code response live in ./negative.tests/
Special control bytes for our protocol live in ./special.bytes/
Control sequences for the Serial Monitor live in ./serial.monitor/
Old packets that somehow fell out of date live in ./broken/

All other packets at this level of the test.packets directory should work as
described by their filenames!

