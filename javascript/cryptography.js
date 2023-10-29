const {
    createHash,
    randomBytes,
    scryptSync,
    timingSafeEqual,
    createHmac,
    createCipheriv,
    createDecipheriv,
    generateKeyPairSync,
    publicEncrypt,
    privateDecrypt,
    createSign,
    createVerify,
} = require("crypto");

// 1
function hash(input, algorithm = "sha256", format = "hex") {
    const hashWithAlgorithm = createHash(algorithm);
    const hashWithAlgorithmAndData = hashWithAlgorithm.update(input);
    const result = hashWithAlgorithmAndData.digest(format);

    return result;
}

// 2
function salt(bytes = 16, format = "hex") {
    const buffer = randomBytes(bytes);
    const result = buffer.toString(format);

    return result;
}

// 3
function hashPassword(input, format = "hex", length = 64) {
    const saltResult = salt();

    const hashedPasswordWithSaltBuffer = scryptSync(input, saltResult, length);
    const hashedPasswordWithSalt =
        hashedPasswordWithSaltBuffer.toString(format);

    const result = `${saltResult}:${hashedPasswordWithSalt}`;

    return result;
}

function matchPassword(input, hashedPassword, format = "hex", length = 64) {
    const [exposedSalt, hashedPasswordWithSalt] = hashedPassword.split(":");

    const hashedInputWithSaltBuffer = scryptSync(input, exposedSalt, length);
    const hashedPasswordWithSaltBuffer = Buffer.from(
        hashedPasswordWithSalt,
        format,
    );

    const safeTimeMatch = timingSafeEqual(
        hashedInputWithSaltBuffer,
        hashedPasswordWithSaltBuffer,
    );

    return safeTimeMatch;
}

// 4
function hmac(input, key, algorithm = "sha256", format = "hex") {
    return createHmac(algorithm, key).update(input).digest(format);
}

// 5
function symmetricEncrypt(
    input,
    key,
    iv,
    algorithm = "aes256",
    inputFormat = "utf8",
    outputFormat = "hex",
) {
    const cipher = createCipheriv(algorithm, key, iv);
    const cipherWithData = cipher.update(input, inputFormat, outputFormat);

    const result = cipherWithData + cipherWithData.final(outputFormat);

    return result;
}

function symmetricDecrypt(
    encryptedInput,
    key,
    iv,
    algorithm = "aes256",
    inputFormat = "hex",
    outputFormat = "utf8",
) {
    const decipher = createDecipheriv(algorithm, key, iv);
    const decipherWithData = decipher.update(
        encryptedInput,
        inputFormat,
        outputFormat,
    );

    const result = decipherWithData + decipherWithData.final(outputFormat);

    return result;
}

// 6
function keyPairs(algorithm = "rsa") {
    const recommendedOptions = {
        modulusLength: 2048,
        publicKeyEncoding: {
            type: "spki",
            format: "pem",
        },
        privateKeyEncoding: {
            type: "pkcs8",
            format: "pem",
            // cipher: "aes-256-cbc",
            // passphrase: "top secret",
        },
    };

    const keys = generateKeyPairSync(algorithm, recommendedOptions);

    return keys;
}

// 7
function asymmetricEncrypt(input, publicKey) {
    const inputBuffer = Buffer.from(input);
    const encryptedDataBuffer = publicEncrypt(publicKey, inputBuffer);

    return encryptedDataBuffer;
}

function asymmetricDecrypt(encryptedInput, privateKey) {
    const decryptedDataBuffer = privateDecrypt(privateKey, encryptedInput);
    return decryptedDataBuffer;
}

// 8
function sign(input, privateKey, algorithm = "rsa-sha256", format = "hex") {
    const signer = createSign(algorithm);
    const signerWithData = signer.update(input);

    const signature = signerWithData.sign(privateKey, format);

    return signature;
}

function verifySign(
    input,
    publicKey,
    signature,
    algorithm = "rsa-sha256",
    format = "hex",
) {
    const verifier = createVerify(algorithm);
    const verifierWithData = verifier.update(input);

    const result = verifierWithData.verify(publicKey, signature, format);

    return result;
}

const message = "Desiderata";

// Hash
const hashResult = hash(message);
console.log("HASH:", hashResult);

// Salt
const saltResult = salt();
console.log("SALT:", saltResult);

// Password
const hashedPassword = hashPassword(message);
console.log("HASHED PASSWORD:", hashedPassword);

const passwordsMatch = matchPassword(message, hashedPassword);
const wrongPasswordsMatch = matchPassword("uwu", hashedPassword);
console.log(passwordsMatch, wrongPasswordsMatch);

// Hmac
const hmacHashResult1 = hmac(message, "uwu");
console.log('HMAC "uwu":', hmacHashResult1);

const hmacHashResult2 = hmac(message, "illo");
console.log('HMAC "illo":', hmacHashResult2);

// Encryption
const key = randomBytes(32);
const iv = randomBytes(16);

const symmetricEncryptResult = symmetricEncrypt(message, key, iv);
console.log("SYMMETRIC ENCRYPT:", symmetricEncryptResult);

const symmetricDecryptResult = symmetricDecrypt(
    symmetricEncryptResult,
    key,
    iv,
);
console.log("SYMMETRIC DECRYPT:", symmetricDecryptResult);

// Key pairs
const { publicKey, privateKey } = keyPairs();
console.log(publicKey);
console.log(privateKey);

// Asymmetric encrypt
const asymmetricEncryptResult = asymmetricEncrypt(message, publicKey);
console.log("ASYMMETRIC ENCRYPT:", asymmetricEncryptResult.toString("hex"));

const asymmetricDecryptResult = asymmetricDecrypt(
    asymmetricEncryptResult,
    privateKey,
);
console.log("ASYMMETRIC DECRYPT:", asymmetricDecryptResult.toString("utf8"));

// Signing
const signatureResult = sign(message, privateKey);
console.log("SIGNATURE:", signatureResult);

const signatureVerificationResult = verifySign(
    message,
    publicKey,
    signatureResult,
);
console.log("SIGNATURE VERIFICATION:", signatureVerificationResult);
