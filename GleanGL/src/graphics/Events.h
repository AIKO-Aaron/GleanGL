#pragma once

namespace Glean {
	namespace events {

		enum EventType {
			UNKNOWN = 0,
			KEYDOWN,
			KEYUP,
			MOUSEMOTION,
			MOUSEDOWN,
			MOUSEUP
		};

		typedef struct {
			EventType type;

		} Event;

	}
}
