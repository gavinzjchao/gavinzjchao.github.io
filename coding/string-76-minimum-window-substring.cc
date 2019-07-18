string minWindow(string s, string t) {
	unordered_map<char, int> mt, ms;

	for (auto c: t)
		mt[c]++;

	int b = 0, e = 0, cnt = 0;
	int s_beg = 0, s_len = INT_MAX;
	while (e < s.length()) {
		if (mt.find(s[e]) == mt.end()) {
			e++;
		} else {
			ms[s[e]]++;
			if (ms[s[e]] <= mt[s[e]]) 
				cnt++;

			if (cnt < t.length()) {
				e++;
			} else {
				while (cnt == t.length()) {
					int cur_len = e - b + 1;
					if (cur_len < s_len) {
						s_beg = b;
						s_len = cur_len;
					}

					if (ms.find(s[b]) != ms.end()) {
						ms[s[b]]--;
						if (ms[s[b]] < mt[s[b]])
							cnt--;
					}

					b++;
				}
				
			}
		}
	}

	return s_len != INT_MAX ? s.substr(s_beg, s_len) : "";
}
