#include "e_d.cpp"
#include "e_d.h"

SUITE(KeyTest)
{	
    TEST(ValidKey)
    {
        vector<char> key = {'2'};
        e_d encryptor(key);
        CHECK_EQUAL("2413", encryptor.encrypt("1234"));
    }
    TEST(InvalidKey)
    {
        vector<char> key = {'-','2'};
        e_d encryptor(key);
        CHECK_EQUAL("2413", encryptor.encrypt("1234"));
    }
    TEST(FloatKey)
    {
        vector<char> key = {'2','.','1'};
        e_d encryptor(key);
        CHECK_EQUAL("2413", encryptor.encrypt("1234"));
    }
    TEST(BigKey)
    {
        vector<char> key = {'1','0','0'};
        e_d encryptor(key);
        CHECK_EQUAL("2413", encryptor.encrypt("1234"));
    }
    TEST(CharKey)
	{
    	vector<char> key = {'2','a'};
    	e_d encryptor(key);
    	CHECK_EQUAL("2413", encryptor.encrypt("1234"));
	}
	TEST(SpaceKey)
	{
    	vector<char> key = {'2',' ','1'};
    	e_d encryptor(key);
    	CHECK_EQUAL("2413", encryptor.encrypt("1234"));
	}
}
SUITE(EncryptTest)
{
	
    TEST(UpString) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("RVTPIE", encryptor.encrypt("PRIVET"));
    }
    TEST(LowString) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("rvtpie", encryptor.encrypt("privet"));
    }

    TEST(PunctuationUndSpaceText)
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("rvtpie", encryptor.encrypt("pri vet!"));
    }

    TEST(DigestText) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("RVT6225PIE8431", encryptor.encrypt("PRIVET86423215"));
    }
    TEST(EmptyString) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("", encryptor.encrypt(""));
    }
}
SUITE(DecryptTest)
{
	
    TEST(UpString) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("PRIVET", encryptor.decrypt("RVTPIE"));
    }
    TEST(LowString) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("privet", encryptor.decrypt("rvtpie"));
    }

    TEST(PunctuationUndSpaceText)
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("privet", encryptor.decrypt("rvt pie!"));
    }

    TEST(DigestText) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("PRIVET86423215", encryptor.decrypt("RVT6225PIE8431"));
    }
    TEST(EmptyString) 
    { 
        vector<char> key = {'2'};
    	e_d encryptor(key);
        CHECK_EQUAL("", encryptor.decrypt(""));
    }
}
int main(int argc, char** argv) {
    return UnitTest::RunAllTests();
}
