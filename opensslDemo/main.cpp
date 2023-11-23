/*
    测试openssl版本为：Win32OpenSSL-1_1_0i

    调试本源码前，必须先安装openssl

    并且，将openssl所在的目录添加到编译器里面，如：C:\OpenSSL-Win32\include

    连接器要添加：C:\OpenSSL-Win32\lib\libcrypto.lib

    windows安装版openssl可以在这里下载：https://oomake.com/download/openssl
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "base64.h"
#include "rsas.h"

using namespace std;


int main(void)
{

    /*私钥是这样的，换行符被换成了\n

    -----BEGIN RSA PRIVATE KEY-----
    MIICWwIBAAKBgQCAhDZFe6UuxD2V2Gjf0HSlCxSWR+92+v9NG+B3sXfjS/uzcSZi
    XeuyaFmTLB6QeCKA5Snou8uZyMNE3Bvdk1So1DPHHLajsHpERRNXiEVdxd60xEEM
    /d/uqtey1napFiTNNStIjIcKb0+8S5Sy4GOsGrscAgRx3wYCAjF6QSqtOQIDAQAB
    AoGAKPq/mXlbSyXNI3ZdvpxoTWZSmrb2b0CK3uoYMeJ3gZVtfaMDY9NiAEIQ6gJj
    /pooGmS4b9tOCUwAo/jxs74yfKctL3HCoQcBfhAyGiyblby+oJ+i4zw8Sxlzjnp7
    yBDZ2lRdDzLEYrab4e6UKTh6YTPNr2nI81JbIxghiA656lcCQQCCjmomitVvOpNm
    a3Nnkh3fEl4tRaZNorY202oXJfO2W7EJfZbJg95HUJqC6mG3o0uOcCr7izQw9N0g
    cBhJbO37AkEA/AALVSWEjKrWR57HTN8Z8jklkSzeiZVD5efT4ReabyeQQ4ZmoHpU
    woOi8e3fo+7NrvTNE8XfBkT4LWY2wHMvWwJAOT42PsX6xTU6sdqFFDFV1ZwZHOKA
    A2RHXoyd5J5oWFmlqxKczah7CmvGA4a+56S6mS6HOhmT/a8vUWy0yWTwhwJAZCuU
    VaVTOiNSiCeqa3kntCxZLYsbbq9BzSrJA2nBfrvIUb8kHlhiRuvSor5+rohnhEtV
    Fa4LCE/0Iv/FddyTjwJAWAUw9vXkEiUhGY9DoPlHynSaaGwpHzgDAPk9meW0AzCy
    WB6kxSQIQIrifhQI3aTqbOjkqFW0O9uT9zLHvVzJ0Q==
    -----END RSA PRIVATE KEY-----
    */

    string pri = "-----BEGIN RSA PRIVATE KEY-----\nMIICWwIBAAKBgQCAhDZFe6UuxD2V2Gjf0HSlCxSWR+92+v9NG+B3sXfjS/uzcSZi\nXeuyaFmTLB6QeCKA5Snou8uZyMNE3Bvdk1So1DPHHLajsHpERRNXiEVdxd60xEEM\n/d/uqtey1napFiTNNStIjIcKb0+8S5Sy4GOsGrscAgRx3wYCAjF6QSqtOQIDAQAB\nAoGAKPq/mXlbSyXNI3ZdvpxoTWZSmrb2b0CK3uoYMeJ3gZVtfaMDY9NiAEIQ6gJj\n/pooGmS4b9tOCUwAo/jxs74yfKctL3HCoQcBfhAyGiyblby+oJ+i4zw8Sxlzjnp7\nyBDZ2lRdDzLEYrab4e6UKTh6YTPNr2nI81JbIxghiA656lcCQQCCjmomitVvOpNm\na3Nnkh3fEl4tRaZNorY202oXJfO2W7EJfZbJg95HUJqC6mG3o0uOcCr7izQw9N0g\ncBhJbO37AkEA/AALVSWEjKrWR57HTN8Z8jklkSzeiZVD5efT4ReabyeQQ4ZmoHpU\nwoOi8e3fo+7NrvTNE8XfBkT4LWY2wHMvWwJAOT42PsX6xTU6sdqFFDFV1ZwZHOKA\nA2RHXoyd5J5oWFmlqxKczah7CmvGA4a+56S6mS6HOhmT/a8vUWy0yWTwhwJAZCuU\nVaVTOiNSiCeqa3kntCxZLYsbbq9BzSrJA2nBfrvIUb8kHlhiRuvSor5+rohnhEtV\nFa4LCE/0Iv/FddyTjwJAWAUw9vXkEiUhGY9DoPlHynSaaGwpHzgDAPk9meW0AzCy\nWB6kxSQIQIrifhQI3aTqbOjkqFW0O9uT9zLHvVzJ0Q==\n-----END RSA PRIVATE KEY-----";

    //原内容
    string data = "你好中国！";

    cout << "\n\n私钥加密前：" << data;

    //私钥加密
    data = rsa_pri_encrypt(data, pri);

    data = base64_encode((const char*)(data.c_str()), data.length());

    cout << "\n\n私钥加密后：" << data;


    /*
    公钥是这样的，换行符也换成了\n
    -----BEGIN PUBLIC KEY-----
    MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCAhDZFe6UuxD2V2Gjf0HSlCxSW
    R+92+v9NG+B3sXfjS/uzcSZiXeuyaFmTLB6QeCKA5Snou8uZyMNE3Bvdk1So1DPH
    HLajsHpERRNXiEVdxd60xEEM/d/uqtey1napFiTNNStIjIcKb0+8S5Sy4GOsGrsc
    AgRx3wYCAjF6QSqtOQIDAQAB
    -----END PUBLIC KEY-----
    */

    std::string pub = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCAhDZFe6UuxD2V2Gjf0HSlCxSW\nR+92+v9NG+B3sXfjS/uzcSZiXeuyaFmTLB6QeCKA5Snou8uZyMNE3Bvdk1So1DPH\nHLajsHpERRNXiEVdxd60xEEM/d/uqtey1napFiTNNStIjIcKb0+8S5Sy4GOsGrsc\nAgRx3wYCAjF6QSqtOQIDAQAB\n-----END PUBLIC KEY-----";

    //base64解码
    data = base64_decode(data);

    //公钥解密
    data = rsa_pub_decrypt(data, pub);

    cout << "\n\n公钥解密后：" << data;

    //公钥加密
    data = rsa_pub_encrypt(data, pub);

    //base64加密
    data = base64_encode((const char*)(data.c_str()), data.length());

    cout << "\n\n公钥加密后：" << data;

    //base64解密
    data = base64_decode(data);

    //私钥解密后
    data = rsa_pri_decrypt(data, pri);

    cout << "\n\n私钥解密后：" << data;

    return 0;
}