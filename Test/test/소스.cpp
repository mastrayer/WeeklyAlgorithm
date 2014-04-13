#include <stdio.h>
#include <string.h>


class Solution {
public:
	/*
	Input String >> Init >> Set Range >> Check Validation >> output
	*/

	void Init(const char *s) // 새 입력이 들어올 때 클래스 초기화
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
		// 문자열의 양 끝단 공백을 제거
		for (int i = 0; i <= mStrlen / 2; ++i)
		{
			if (mStartIndex == -1 && s[i] != ' ')				mStartIndex = i;
			if (mEndIndex == -1 && s[mStrlen - i - 1] != ' ')	mEndIndex = mStrlen - i - 1;
			if (mStartIndex != -1 && mEndIndex != -1)			break;
		}

		// 공백으로만 이루어진 문자열
		if (mStartIndex == -1 || mEndIndex == -1)
			return false;
		return true;
	}

	// 입력된 문자열이 숫자인지 검사
	/*

	1. 앞 뒤 공백을 모두 지운다.
	2. -, +는 무조건 맨 앞자리에 와야한다.
	3. .은 양쪽 끝단에 위치할 수 없다.
	4. e는 양쪽 끝단에 위치할 수 없다.
	5. 숫자가 아닌 문자가 존재하면 안된다. (e, ., - 제외)
	6. 문자 사이에 공백이 존재하면 안된다.
	7. e뒤에 .이 올 수 없다.


	// 애매모호해서 예외처리 안한것들

	e의 지수로 정수만 가능 ( 양수 )
	e+12, e-12 이런거 안됨. e12만 가능
	e10 이런거 안됨. ( 1e10 이라고 써야함)

	입력되는 숫자가 10진수인지 판별 ( 16진수 아님. 알파벳 사용 불가 )

	.12 이런거 안됨. ( 0.12 라고 써야함 )

	띄어쓰기 안됨. ( 1 2 같은거 안됨. 12라고 써야함 )

	문자열의 처음과 끝 문자가 "가 아니다.

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
				if (i == mStartIndex) // 처음 문자.
				{
					// 2.
					if (ch == '+' || ch == '-') continue;
				}
				else if (i != mEndIndex) // 양 끝단에 위치하지 않은 문자
				{
					// 3.
					if (ch == '.')
					{
						if (e == true)		return false;		// e의 지수로 소수가 올 수 없음
						if (point == true)	return false;	// .이 2개 이상 존재
						point = true;

						continue;
					}
					// 4.
					else if (ch == 'e' || ch == 'E')
					{
						if (e == true)		return false; // e가 2개 이상 존재
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
	int mStartIndex, mEndIndex; // 검사할 문자열의 Index
	int mStrlen;				// 문자열의 길이
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