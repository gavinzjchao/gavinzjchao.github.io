vector<int> countBits1(int num) {
	vector<int> res(num + 1, 0);

	for (int i = 1; i <= num; i++) {
		res[i] = res[i >> 1] + (i & 1);
	}

	return res;
}

vector<int> countBits(int num) {
	vector<int> res(num + 1, 0);

	int pow2 = 1;
	int pos = 1;
	for (int i = 1; i <= num; i++) {
		if (i == pow2) {
			res[i] = 1;
			pos = 1;
			pow2 = pow2 << 1;
		} else {
			res[i] = res[pos] + 1;
			pos++;
		}
	}

	return res;
}
