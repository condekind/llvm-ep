#define BUF_SIZE 120  // works if changed to 132

int read_matrix(int *data, char w, char h) {
	char buf_size = w * h;
	if (buf_size < BUF_SIZE) {
		int c0, c1;
		int buf[BUF_SIZE];
		for (c0 = 0; c0 < h; c0++) {
			for (c1 = 0; c1 < w; c1++) {
				int index = c0 * w + c1;
				buf[index] = data[index];
			}
		}
		return buf[0];
	}
}

int main()
{
	int x[22][6];
	int y = read_matrix((int *)x, 6, 22);
	return 0;
}