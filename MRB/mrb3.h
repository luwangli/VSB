#ifndef DEFINE_MRBITMAP
#define DEFINE_MRBITMAP

#include <math.h>

template <std::size_t R, std::size_t N>
class MRBitmap {
	private:
		unsigned long long *bitmap[R];
		long long count[R];
		int h;

	public:
		MRBitmap () {
			int d = 1;
			for (int i = 0; i < R; i++) {
				bitmap[i] = new unsigned long long[N / (d * 64) + 1];
				d <<= 1;
				count[i] = 0;
			}
		}

		void insert (int idx) {
			idx = idx % (R * N);

			int r = idx / N;

			idx = idx % N;
			idx = idx / (1 << r);

			int i = idx / 64;
			int j = idx % 64;

			int setBefore = __builtin_popcount(bitmap[r][i]);
			bitmap[r][i] |= (1 << j);
			int setAfter = __builtin_popcount(bitmap[r][i]);

			if (setBefore != setAfter) {
				count[r]++;
			}
		}

		void clear() {
			for(int i = 0; i < R; i++) {
				memset(bitmap[i], 0, sizeof bitmap[i]);
				count[i] = 0;
			}
		}

		int getCount() {
			int base = 1;
			int setMax = (N / (1 << base)) * (1.0 - pow(2.7182, -3.1426));

			while (base < R && count[base] <=  setMax) {
				base++;
				setMax = (N / (1 << base)) * (1.0 - pow(2.7182, -3.1426));
			}

			base--;

			int m = 0;
			for (int i = 0; i <= base; i++) {
				float sizeR = N / (1 << i);
				m +=  sizeR * log(sizeR / (sizeR - count[i]));
			}

			int factor = 1 << (R - base - 1);
			return m * R;
		}
};

#endif
