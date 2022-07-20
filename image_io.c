#include "image_io.h"
bool Image_Read_Jpeg(char* filename,Image** OriImage)
{
    FILE * infile = fopen(filename, "rb");
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    int width = cinfo.output_width;
    int height = cinfo.output_height;
    int channel = cinfo.output_components;
     unsigned char* data = (unsigned char *) malloc(cinfo.output_height * cinfo.output_width * cinfo.output_components*sizeof(unsigned char));
    unsigned char *line_pointer;
    int i = 0;
    while (cinfo.output_scanline < cinfo.image_height) {
        line_pointer = data + i * cinfo.output_width * cinfo.output_components;
        jpeg_read_scanlines(&cinfo, &line_pointer, 1); 
        i ++;
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
     if(channel==1)
     {
        (*OriImage)=Image_Create_FArry(data,width*height*channel,width,height,IMAGE_FORMAT_GRAY);
     }
     else
         (*OriImage)= Image_Create_FArry(data,width*height*channel,width,height,IMAGE_FORMAT_RGB);
    return true;

}
M_ErrMsg Image_Write_Jpeg(char* filename,Image* OriImage)
 {
   struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    int row_stride = 0;
    FILE* fp = NULL;
    unsigned char* img_data;
    Image_Convert_TArray(OriImage,&img_data);
    JSAMPROW row_pointer[1];
    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_compress(&cinfo);
    fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("open file %s failed.\n", fp);
        return M_ERR_WRITEERROR;
    }
    jpeg_stdio_dest(&cinfo, fp);
    cinfo.image_width = OriImage->image_width;
    cinfo.image_height =  OriImage->image_height;
    cinfo.input_components =  OriImage->image_channel;
    switch (OriImage->image_channel)
    {
    case 1:
        /* code */
         cinfo.in_color_space = JCS_GRAYSCALE;//设置输入格式
        break;
    case 3:
     cinfo.in_color_space = JCS_RGB;//设置输入格式
    break;
    default:
        break;
    }
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, 1);  // todo 1 == true
    jpeg_start_compress(&cinfo, TRUE);
    row_stride = OriImage->image_width * cinfo.input_components;
    
    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &img_data[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    M_Free(img_data);
    fclose(fp);
 }
 