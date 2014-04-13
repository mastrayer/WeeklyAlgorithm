#include <stdio.h>
#include <string.h>


class Solution {
public:
	/*
	Input String >> Init >> Set Range >> Check Validation >> output
	*/

	void Init(const char *s) // �� �Է��� ���� �� Ŭ���� �ʱ�ȭ
	{
		mStrlen = strlen(s);
		mStartIndex = mEndIndex = - 1;
	}

	bool isNumber(const char *s) {
		Init(s);

		if (SetRange(s) == false) return false;
		return isValid(s);
	}

	bool SetRange(const char *s)
	{
		// ���ڿ��� �� ���� ������ ����
		for (int i = 0; i <= mStrlen / 2; ++i)
		{
			if (mStartIndex == -1 && s[i] != ' ')				mStartIndex = i;
			if (mEndIndex == -1 && s[mStrlen - i - 1] != ' ')	mEndIndex = mStrlen - i - 1;
			if (mStartIndex != -1 && mEndIndex != -1)			break;
		}

		// �������θ� �̷���� ���ڿ�
		if (mStartIndex == -1 || mEndIndex == -1)
			return false;
		return true;
	}

	// �Էµ� ���ڿ��� �������� �˻�
	/*

	1. �� �� ������ ��� �����.
	2. -, +�� ������ �� ���ڸ��� �;��Ѵ�.
	3. .�� ���� ���ܿ� ��ġ�� �� ����.
	4. e�� ���� ���ܿ� ��ġ�� �� ����.
	5. ���ڰ� �ƴ� ���ڰ� �����ϸ� �ȵȴ�. (e, ., - ����)
	6. ���� ���̿� ������ �����ϸ� �ȵȴ�.
	7. e�ڿ� .�� �� �� ����.


	// �ָŸ�ȣ�ؼ� ����ó�� ���Ѱ͵�

	e�� ������ ������ ���� ( ��� )
	e+12, e-12 �̷��� �ȵ�. e12�� ����
	e10 �̷��� �ȵ�. ( 1e10 �̶�� �����)

	�ԷµǴ� ���ڰ� 10�������� �Ǻ� ( 16���� �ƴ�. ���ĺ� ��� �Ұ� )

	.12 �̷��� �ȵ�. ( 0.12 ��� ����� )

	���� �ȵ�. ( 1 2 ������ �ȵ�. 12��� ����� )

	���ڿ��� ó���� �� ���ڰ� "�� �ƴϴ�.

	*/
	bool isValid(const char *s)
	{
		bool e = false;
		bool point = false;

		for (int i = mStartIndex; i <= mEndIndex; ++i)
		{
			char ch = s[i];

			if (!(ch >= '0' && ch <= '9')) // 5. 
			{
				if (i == mStartIndex) // ó�� ����.
				{
					// 2.
					if (ch == '+' || ch == '-') continue;
				}
				else if (i != mEndIndex) // �� ���ܿ� ��ġ���� ���� ����
				{
					// 3.
					if (ch == '.')
					{
						if (e == true)		return false;		// e�� ������ �Ҽ��� �� �� ����
						if (point == true)	return false;	// .�� 2�� �̻� ����
						point = true;

						continue;
					}
					// 4.
					else if (ch == 'e' || ch == 'E')
					{
						if (e == true)		return false; // e�� 2�� �̻� ����
						e = true;

						continue;
					}
				}
				return false;
			}
		}

		return true;
	}

private:
	int mStartIndex, mEndIndex; // �˻��� ���ڿ��� Index
	int mStrlen;				// ���ڿ��� ����
};

#define CASENUM 5
int main()
{
	Solution sol;
	char TestCase[CASENUM][20] = { "   1.1e12    ", "  -112.2", " 0.000002e5", "23 - 12", " 2e10" };

	for (int i = 0; i < CASENUM; ++i)
	{
		printf("\"%s\" is %d\n",TestCase[i], sol.isNumber(TestCase[i]));
	}

	getchar();
	return 0;
}