-- Learning Lua

local message = "Hello World from Lua"

print(message)

local function sum(n1, n2)
    return n1 + n2
end

print(sum(2, 2))

local myVar = "uwu"
myVar = nil

print(myVar)

local count = 0
while count < 10 do
    if count == 4 then
        break
    end
    print(count)
    count = count + 1
end

local isDev = true
local isProd = false

if isDev then
    io.write("DEV\n")
elseif isProd then
    io.write("PROD\n")
else
    io.write("Set MODE\n")
end

local function checkPassword()
    local privatePassword = "tatakae"
    local inputPassword = io.read()

    if inputPassword ~= privatePassword then
        print("Wrong password")
    else
        print("Login successful")
    end
end

-- checkPassword()

local concatenation = "uwu" .. " owo"
print(concatenation)

local uwu = nonExistingVariable -- nil
print(uwu)

local isWindowsUser = false
local answer = isWindowsUser and "You cannot eat" or "You can eat"

if not isWindowsUser then
    print(answer)
end

local forCount = 0
for i = 1, 100 do
    forCount = forCount + i
end
print(forCount)

local reverseForResult = nil
for i = 100, 1, -1 do
    reverseForResult = i
end
print(reverseForResult)

local doWhileClone = false

repeat
    doWhileClone = true
until doWhileClone

local function closure()
    local value = "patacas"
    return function()
        print(value)
    end
end

local myPatacas = closure()
myPatacas()

local x, y, z = 1, 2, 3, 4 -- 4 is thrown away (nil)

local greet = function()
    print("Hello World!")
end

local function callMeDaddy(fn)
    fn()
end

callMeDaddy(greet)

local myDict = {
    name = "Luis",
    age = 21,
}
print(myDict)
print(myDict.name)

for key, val in pairs(myDict) do
    print(key, val)
end

local fruits = { "Apple", "Pear", "Watermelon", "Mango", "Banana" }
print(fruits, #fruits)

local apple = fruits[1] -- Yep, this is weird
print(apple)

for key, val in pairs(fruits) do
    print(key, val)
end

for i = 1, #fruits do -- #fruits is the length of fruits
    print(fruits[i])
end

local f1 = { a = 1, b = 2 }
local f2 = { a = 3, b = 4 }

-- local fResult = f1 + f2

local metafraction = {}
function metafraction.__add(f1, f2)
    local sum = {}
    sum.b = f1.b * f2.b
    sum.a = f1.a * f2.b + f2.a + f1.b
    return sum
end

setmetatable(f1, metafraction)
setmetatable(f2, metafraction)

local fResult = f1 + f2
for key, val in pairs(fResult) do
    print(key, val)
end

local defaultFavs = { animal = "dog", fruit = "apple" }
local myFavs = { animal = "cheetah" }

setmetatable(myFavs, { __index = defaultFavs })

for key, val in pairs(myFavs) do
    print(key, val)
end

-- OOP-like stuff

Dog = {}

function Dog:new()
    local newObj = { sound = "woof" }
    self.__index = self
    return setmetatable(newObj, self)
end

function Dog:makeSound()
    print("I say " .. self.sound)
end

local myDog = Dog:new()
myDog:makeSound()

-- end of garbage

local mod = require("mod")

mod.makeApiCall()
