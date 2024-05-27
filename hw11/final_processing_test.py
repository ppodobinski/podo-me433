### FROM https://realpython.com/image-processing-with-the-python-pillow-library/

from PIL import Image
filename = "get_image_pil.jpg"
with Image.open(filename) as img:
    img.load()

# img.show()

cropped_img = img.crop((300, 150, 700, 1000))
cropped_img.size
low_res_img = cropped_img.reduce(4)
cropped_img.save("cropped_image.jpg")
low_res_img.save("low_resolution_cropped_image.png")

converted_img = img.transpose(Image.FLIP_TOP_BOTTOM)
converted_img.save("converted_image.jpg")