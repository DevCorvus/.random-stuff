const _ = require("lodash");

function isObject(value) {
    return value && typeof value === "object" && !Array.isArray(value);
}

function isArray(value) {
    return Array.isArray(value);
}

function cloneDeepObject(obj) {
    if (!isObject(obj)) throw new Error("Not an object");

    const out = {};

    // Object.entries() is the devil. Too slow!
    for (const key in obj) {
        const value = obj[key];

        if (isObject(value)) {
            out[key] = cloneDeepObject(value);
            continue;
        }

        if (isArray(value)) {
            out[key] = cloneDeepArray(value);
            continue;
        }

        out[key] = value;
    }

    return out;
}

function cloneDeepArray(arr) {
    if (!isArray(arr)) throw new Error("Not an array");

    return arr.map((item) => {
        if (isObject(item)) return cloneDeepObject(item);
        if (isArray()) return cloneDeepArray(item);
        return item;
    });
}

function cloneDeep(value) {
    if (isObject(value)) {
        return cloneDeepObject(value);
    }

    if (isArray(value)) {
        return cloneDeepArray(value);
    }

    throw new Error("Neither an Object or Array");
}

function mergeDeepObject(obj1, obj2) {
    const out = cloneDeepObject(obj1);

    for (const key in obj2) {
        const value = obj2[key];

        if (out.hasOwnProperty(key)) {
            if (isObject(out[key]) && isObject(value)) {
                out[key] = mergeDeepObject(out[key], value);
            } else if (isArray(out[key]) && Array.isArray(value)) {
                out[key] = mergeDeepArray(out[key], value);
            }
            continue;
        }

        if (isObject(value)) {
            out[key] = cloneDeepObject(value);
            continue;
        }

        if (isArray(value)) {
            out[key] = cloneDeepArray(value);
            continue;
        }

        out[key] = value;
    }

    return out;
}

function mergeDeepArray(arr1, arr2) {
    return [...cloneDeepArray(arr1), ...deepCopyArray(arr2)];
}

function mergeDeep(val1, val2) {
    if (isObject(val1) && isObject(val2)) {
        return mergeDeepObject(val1, val2);
    }

    if (isArray(val1) && Array.isArray(val2)) {
        return mergeDeepArray(val1, val2);
    }

    throw new Error("Both values should be either Objects or Arrays");
}

const obj1 = { name: "Luis", age: 21, phone: { work: "1731255" } };
const obj2 = {
    age: 44,
    isMale: true,
    phone: { home: "51283912" },
    list: ["owo"],
};

const result = mergeDeep(obj1, obj2);

obj1.age = 44;
obj2.phone.home = "uwu";
obj2.list.push("uwu");

console.log(result);

console.log("Comparing deep clone techniques:\n");

// This is amazing. Almost x10 increase in performance!
const iterations = 1_000_000;
console.time("My cloneDeep object");
for (let i = 0; i < iterations; i++) {
    cloneDeep(obj2);
}
console.timeEnd("My cloneDeep object");

console.time("Stringify and parse object");
for (let i = 0; i < iterations; i++) {
    JSON.parse(JSON.stringify(obj2));
}
console.timeEnd("Stringify and parse object");

console.time("Native structuredClone object");
for (let i = 0; i < iterations; i++) {
    structuredClone(obj2);
}
console.timeEnd("Native structuredClone object");

console.time("Lodash cloneDeep object");
for (let i = 0; i < iterations; i++) {
    _.cloneDeep(obj2);
}
console.timeEnd("Lodash cloneDeep object");
