function convertToFormat(data, dataFormat, expectedFormat) {
  const buffer = Buffer.from(data, dataFormat);
  const result = buffer.toString(expectedFormat);

  return result;
}

function textToBinary(text) {
  //const chars = text.split('');

  const binaryCodes = [];

  for (let i = 0; i < text.length; i++) {
    // const char = chars[i];
    // const charCode = char.charCodeAt(0);
    const charCode = text.charCodeAt(i);
    const binCode = charCode.toString(2);

    binaryCodes.push(binCode);
  }

  const binaryString = binaryCodes.join(" ");

  return binaryString;
}

function binaryToText(binaryString) {
  const binaryCodes = binaryString.split(" ");

  let text = "";

  for (let i = 0; i < binaryCodes.length; i++) {
    const binCode = binaryCodes[i];

    const charCode = parseInt(binCode, 2);
    const char = String.fromCharCode(charCode);

    text += char;
  }

  return text;
}

const message = "Desiderata";
console.log(message);

// Binary
const binary = textToBinary(message);
console.log("BINARY:", binary);

const binaryResult = binaryToText(binary);
console.log("BINARY RESULT:", binaryResult);

// Ascii
const ascii = convertToFormat(message, "utf8", "ascii");
console.log("ASCII:", ascii);

const asciiResult = convertToFormat(ascii, "ascii", "utf8");
console.log("ASCII RESULT:", asciiResult);

// Hex
const hex = convertToFormat(message, "utf8", "hex");
console.log("HEX:", hex);

const hexResult = convertToFormat(hex, "hex", "utf8");
console.log("HEX RESULT:", hexResult);

// Base64
const base64 = convertToFormat(message, "utf8", "base64");
console.log("BASE64:", base64);

const base64Result = convertToFormat(base64, "base64", "utf8");
console.log("BASE64 RESULT:", base64Result);

// Base64Url
const base64Url = convertToFormat(message, "utf8", "base64url");
console.log("BASE64 URL:", base64Url);

const base64UrlResult = convertToFormat(hex, "base64url", "utf8");
console.log("BASE64 URL RESULT:", base64UrlResult);
