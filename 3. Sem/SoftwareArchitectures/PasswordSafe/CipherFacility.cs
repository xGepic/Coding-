using System.Security.Cryptography;
using System.Text;

namespace PasswordSafeConsole
{
    internal class CipherFacility
    {
        private readonly string masterPw;
        public CipherFacility(string masterPw)
        {
            this.masterPw = masterPw;
        }
        public string Decrypt(byte[] crypted)
        {
            var key = GetKey(this.masterPw);
            using var aes = Aes.Create();
            using var decryptor = aes.CreateDecryptor(key, key);
            var decryptedBytes = decryptor.TransformFinalBlock(crypted, 0, crypted.Length);
            return Encoding.UTF8.GetString(decryptedBytes);
        }
        public byte[] Encrypt(string plain)
        {
            var key = GetKey(this.masterPw);
            using var aes = Aes.Create();
            using var encryptor = aes.CreateEncryptor(key, key);
            var plainText = Encoding.UTF8.GetBytes(plain);
            return encryptor.TransformFinalBlock(plainText, 0, plainText.Length);
        }
        private static byte[] GetKey(string password)
        {
            var keyBytes = Encoding.UTF8.GetBytes(password);
            using var md5 = MD5.Create();
            return md5.ComputeHash(keyBytes);
        }
        //The encryption method for the passwords should be exchangeable. Right now, the app
        //supports only AES and there is no easy/foreseen way to introduce another algorithm.
        //It would be great to switch between already implemented methods by proper configuration settings.
        public byte[] Encrypt2(string plain)
        {
            string SecurityKey = this.masterPw;
            byte[] toEncryptedArray = UTF8Encoding.UTF8.GetBytes(plain);// Getting the bytes of Input String.
            MD5CryptoServiceProvider objMD5CryptoService = new(); //Getting the bytes from the Security Key and Passing it to compute the Corresponding Hash Value.
            byte[] securityKeyArray = objMD5CryptoService.ComputeHash(UTF8Encoding.UTF8.GetBytes(SecurityKey));
            objMD5CryptoService.Clear(); //De-allocatinng the memory after doing the Job.
            var objTripleDESCryptoService = new TripleDESCryptoServiceProvider
            {
                Key = securityKeyArray,//Assigning the Security key to the TripleDES Service Provider.
                Mode = CipherMode.ECB,//Mode of the Crypto service is Electronic Code Book.
                Padding = PaddingMode.PKCS7//Padding Mode is PKCS7 if there is any extra byte is added.
            };
            var objCrytpoTransform = objTripleDESCryptoService.CreateEncryptor();
            byte[] resultArray = objCrytpoTransform.TransformFinalBlock(toEncryptedArray, 0, toEncryptedArray.Length); //Transform the bytes array to resultArray
            objTripleDESCryptoService.Clear();
            return resultArray;
        }
        public string Decrypt2(byte[] crypted)
        {
            string SecurityKey = this.masterPw;
            MD5CryptoServiceProvider objMD5CryptoService = new();
            byte[] securityKeyArray = objMD5CryptoService.ComputeHash(UTF8Encoding.UTF8.GetBytes(SecurityKey)); //Getting the bytes from the Security Key and Passing it to compute the Corresponding Hash Value.
            objMD5CryptoService.Clear();
            var objTripleDESCryptoService = new TripleDESCryptoServiceProvider
            {
                Key = securityKeyArray, //Assigning the Security key to the TripleDES Service Provider.
                Mode = CipherMode.ECB,  //Mode of the Crypto service is Electronic Code Book.
                Padding = PaddingMode.PKCS7 //Padding Mode is PKCS7 if there is any extra byte is added.
            };
            var objCrytpoTransform = objTripleDESCryptoService.CreateDecryptor();
            byte[] resultArray = objCrytpoTransform.TransformFinalBlock(crypted, 0, crypted.Length);//Transform the bytes array to resultArray
            objTripleDESCryptoService.Clear();
            return UTF8Encoding.UTF8.GetString(resultArray); //Convert and return the decrypted data/byte into string format.
        }
    }
}