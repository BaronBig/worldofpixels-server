#include <chrono>

namespace limiter {
	class Bucket {
		uint16_t rate;
		uint16_t per;
		float allowance;
		std::chrono::steady_clock::time_point last_check;
	public:
		Bucket(const uint16_t rate, const uint16_t per);
		bool can_spend(const uint16_t = 1);
		void change_rate(const uint16_t);
		uint16_t get_rate() const;
	};
	
	class Simple {
		float rate;
		std::chrono::steady_clock::time_point last_check;
	public:
		Simple(const float rate);
		bool can_spend();
	};
}
