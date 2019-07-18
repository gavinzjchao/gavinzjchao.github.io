bool isMatch(string s, string p) {
	int i = 0, j = 0, i_star = -1, j_star = -1;

	while (i < s.length()) {
		if (s[i] == p[j] || p[j] == '?') {
			i++;
			j++;
		} else if (p[j] == '*') {
			i_star = i;
			j_star = j++; // *可以匹配0 - 无数个任意子序列，因此确保i不变，让j先走一步
		} else if (i_star >= 0) {
			i = ++i_star; // 直接略过一个字符，因为* 可以匹配0或多个任意字符
			j = j_star + 1; // 回跳到*号后面继续匹配
		} else {
			return false;
		}
	}

	while (j < p.length() && p[j] == '*')
		j++;

	return j == p.length();
}
