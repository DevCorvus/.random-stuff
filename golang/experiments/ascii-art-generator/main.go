package main

import (
	"errors"
	"flag"
	"fmt"
	"image"
	"image/color"
	"image/jpeg"
	"image/png"
	"mime"
	"os"
	"path/filepath"
	"slices"
	"strings"

	gookitColor "github.com/gookit/color"
)

type RGB struct {
	red   uint32
	green uint32
	blue  uint32
}

type Luminance struct {
	red   uint32
	gray  uint32
	mixed uint32
	luma  uint32
}

type PixelInfo struct {
	luminance Luminance
	color     RGB
}

const MAX_LUMINANCE uint32 = 255

var asciiChars = [8]byte{' ', '.', ',', '-', '~', '+', '=', '@'}
var luminanceTypes = []string{"red", "gray", "mixed", "luma"}

var maxSize int
var luminanceType string = "red"

func openImageFile(filePath string) (image.Image, error) {
	mimeType := mime.TypeByExtension(filepath.Ext(filePath))

	if mimeType == "" {
		return nil, errors.New("Unknown file type")
	}

	fileType := strings.Split(mimeType, "/")[1]

	if fileType != "jpeg" && fileType != "png" {
		return nil, errors.New("Only JPEG and PNG files are supported")
	}

	file, err := os.Open(filePath)

	if err != nil {
		return nil, err
	}

	defer file.Close()

	var img image.Image
	var decodeErr error

	if fileType == "jpeg" {
		img, decodeErr = jpeg.Decode(file)
	} else {
		img, decodeErr = png.Decode(file)
	}

	if decodeErr != nil {
		return nil, err
	}

	return img, nil
}

func getDynamicStep(width, height int) int {
	widthScale := width / maxSize
	heightScale := height / maxSize
	return max(widthScale, heightScale, 1)
}

func getPixelInfo(img image.Image, x, y int) PixelInfo {
	pixel := img.At(x, y)

	r, g, b, _ := pixel.RGBA()

	r /= 256
	g /= 256
	b /= 256

	rGray, _, _, _ := color.GrayModel.Convert(pixel).RGBA()

	luma := uint32((float64(r) * 0.2126) + (float64(g) * 0.7152) + (float64(b) * 0.0722))

	return PixelInfo{
		luminance: Luminance{
			red:   r,
			gray:  rGray >> 8, // Same as dividing by 256 but faster
			mixed: r/3 + g/3 + b/3,
			luma:  luma,
		},
		color: RGB{
			red:   r,
			green: g,
			blue:  b,
		},
	}
}

func getAsciiChar(luminance uint32) byte {
	index := uint32((float64(luminance) / float64(MAX_LUMINANCE)) * float64(len(asciiChars)))

	if luminance == MAX_LUMINANCE {
		index = uint32(len(asciiChars) - 1)
	}

	return asciiChars[index]
}

func getLuminance(luminance Luminance) uint32 {
	var value uint32

	switch luminanceType {
	case "red":
		value = luminance.red
	case "gray":
		value = luminance.gray
	case "mixed":
		value = luminance.mixed
	case "luma":
		value = luminance.luma
	}

	return value
}

func printColoredAsciiChar(asciiChar string, color RGB) {
	gookitColor.RGB(uint8(color.red), uint8(color.green), uint8(color.blue)).Printf(asciiChar)
}

func generateAsciiArt(filePath string) error {
	img, err := openImageFile(filePath)

	if err != nil {
		return err
	}

	bounds := img.Bounds()

	width := bounds.Max.X
	height := bounds.Max.Y

	step := getDynamicStep(width, height)

	for y := 0; y < height; y += (step * 2) {
		var row strings.Builder

		for x := 0; x < width; x += step {
			info := getPixelInfo(img, x, y)

			luminance := getLuminance(info.luminance)
			asciiChar := getAsciiChar(luminance)

			row.WriteByte(asciiChar)
		}

		fmt.Println(row.String())
	}

	return nil
}

func generateColoredAsciiArt(filePath string) error {
	img, err := openImageFile(filePath)

	if err != nil {
		return err
	}

	bounds := img.Bounds()

	width := bounds.Max.X
	height := bounds.Max.Y

	step := getDynamicStep(width, height)

	for y := 0; y < height; y += (step * 2) {
		for x := 0; x < width; x += step {
			info := getPixelInfo(img, x, y)

			luminance := getLuminance(info.luminance)
			asciiChar := getAsciiChar(luminance)

			printColoredAsciiChar(string(asciiChar), info.color)
		}

		fmt.Println()
	}

	return nil
}

func main() {
	filePathFlag := flag.String("file", "", "Required file path argument")
	maxSizeFlag := flag.Uint("size", 200, "Max size for width and height in characters")
	coloredFlag := flag.Bool("colored", false, "Generate colored ascii art (slower)")
	luminanceTypeFlag := flag.String("luminance", "red", "Type of luminance (red/gray/mixed/luma) Default: red")

	flag.Parse()

	if *filePathFlag == "" {
		fmt.Println("Missing required path argument")
		flag.PrintDefaults()
		os.Exit(1)
	}

	if *maxSizeFlag == 0 {
		fmt.Println("Max size must not be zero")
		os.Exit(1)
	}

	maxSize = int(*maxSizeFlag)

	if !slices.Contains(luminanceTypes, *luminanceTypeFlag) {
		fmt.Println("Invalid luminance type")
		os.Exit(1)
	}

	luminanceType = *luminanceTypeFlag

	var err error

	if *coloredFlag {
		err = generateColoredAsciiArt(*filePathFlag)
	} else {
		err = generateAsciiArt(*filePathFlag)
	}

	if err != nil {
		fmt.Println(err.Error())
		os.Exit(1)
	}
}
