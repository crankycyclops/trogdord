#ifndef OUTPUT_MESSAGE_H
#define OUTPUT_MESSAGE_H

#include <string>
#include <ctime>

#include "../json.h"

namespace output {


	// Represents a single message to be inserted into the output buffer.
	struct Message {

		// If I use time_t, I'll get a build error from RapidJSON when compiling
		// for armhf, a 32-bit architecture. The solution to use uint64_t comes
		// from: https://github.com/Tencent/rapidjson/issues/1429
		// I believe that on armhf, time_t is a 32-bit integer, and I think
		// that's somehow gumming up the works. Not going to bother diving too
		// deep as long as this fix works.
		uint64_t timestamp;

		std::string content;
		size_t order = 0;

		// Converts Message to a JSON object
		rapidjson::Value toJSONObject(rapidjson::MemoryPoolAllocator<> &allocator) {

			rapidjson::Value o(rapidjson::kObjectType);
			rapidjson::Value val(rapidjson::kStringType);

			val.SetString(rapidjson::StringRef(content.c_str()), allocator);

			o.AddMember("timestamp", timestamp, allocator);
			o.AddMember("content", val, allocator);
			o.AddMember("order", order, allocator);

			return o;
		}
	};
}


#endif
