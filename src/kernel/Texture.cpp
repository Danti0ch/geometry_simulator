#include "Texture.h"
#include <assert.h>
#include "Pixel.h"
#include "glib_wrapper.h"

void draw_solid(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask, double transparency_ratio);
void draw_filled(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask);
void draw_scretched(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask);
void draw_distribution(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask, TEXTURE_INSERT_MODE mode, double transparency_ratio);

// TODO: filled and scretched
//========================================================================================//

//                          PUBLIC_FUNCTIONS_DEFINITION

//========================================================================================//
static Pixel pix = Pixel(0, 0, WHITE);

#include <iostream>
void Texture::draw(PixelBuffer* buff, uint x_l, uint y_l, uint x_u, uint y_u, TEXTURE_INSERT_MODE mode){

    draw_distribution(*this, buff, x_l, y_l, x_u, y_u, false, pt_set(), mode, transparency_ratio_);
    return;
}
//----------------------------------------------------------------------------------------//

void Texture::draw(PixelBuffer* buff, uint x_l, uint y_l, uint x_u, uint y_u, const pt_set& mask, TEXTURE_INSERT_MODE mode){
    
    draw_distribution(*this, buff, x_l, y_l, x_u, y_u, true, mask, mode, transparency_ratio_);    
    return;
}

void Texture::setTransparency(double val){
    assert(val >= 0);

    if(val > 1) val = 1;

    transparency_ratio_ = val;
    return;
}

//========================================================================================//

//                          LOCAL_FUNCTIONS_DEFINITION

//========================================================================================//


void draw_distribution(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask, TEXTURE_INSERT_MODE mode, double transparency_ratio){

    assert(space != NULL);

    if(x_l == x_u || y_l == y_u) return;

    if(obj.is_solid()){
        draw_solid(obj, space, x_l, y_l, x_u, y_u, mask_req, mask, transparency_ratio);
        return;
    }
    
         if(mode == TEXTURE_INSERT_MODE::FILLING)    draw_scretched(obj, space, x_l, y_l, x_u, y_u, mask_req, mask);
    else if(mode == TEXTURE_INSERT_MODE::SCRETCHING) draw_filled(obj, space, x_l, y_l, x_u, y_u, mask_req, mask);

    return;
}
//----------------------------------------------------------------------------------------//

void draw_filled(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask){

    assert(space != NULL);

    uint x_tr_pxs = obj.col_pixels().n_cols();
    uint y_tr_pxs = obj.col_pixels().n_rows();

    uint ny_area_pxs = y_u - y_l + 1;
    uint nx_area_pxs = x_u - x_l + 1;

    std::vector<Pixel> pixs_to_draw;

    uint y_tr_ind = 0, x_tr_ind = 0;

    for(uint y_ind = 0; y_ind < ny_area_pxs; y_ind++, y_tr_ind++){
        if(y_ind >= y_tr_pxs) y_tr_ind = 0;

        for(uint x_ind = 0; x_ind < nx_area_pxs; x_ind++, x_tr_ind++){
            if(x_ind >= x_tr_pxs) x_tr_ind = 0;

            if(!mask_req || mask.count({y_ind, x_ind})){
                pixs_to_draw.push_back(Pixel(y_l + y_ind, x_l + x_ind, obj.col_pixels().get(y_tr_ind, x_tr_ind)));
            }
        }
    }
    
    space->drawPixels(pixs_to_draw);
    return;
}
//----------------------------------------------------------------------------------------//

void draw_scretched(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask){

    assert(space != NULL);

    uint x_tr_pxs = obj.col_pixels().n_cols();
    uint y_tr_pxs = obj.col_pixels().n_rows();

    uint ny_area_pxs = y_u - y_l + 1;
    uint nx_area_pxs = x_u - x_l + 1;
    
    std::vector<Pixel> pixs_to_draw;

    double x_scr_ratio = (double)x_tr_pxs / (double)nx_area_pxs;
    double y_scr_ratio = (double)y_tr_pxs / (double)ny_area_pxs;
    
    for(uint n_row = 0; n_row < ny_area_pxs; n_row++){
        for(uint n_col = 0; n_col < nx_area_pxs; n_col++){
            if(!mask_req || mask.count({n_row, n_col})){

                Color cur_col = obj.col_pixels().get((uint)(n_row * y_scr_ratio), (uint)(n_col * x_scr_ratio));
                pixs_to_draw.push_back(Pixel(y_l + n_row, x_l + n_col, cur_col));
            }
        }
    }

    space->drawPixels(pixs_to_draw);
    return;
}
//----------------------------------------------------------------------------------------//

void draw_solid(const Texture& obj, PixelBuffer* space, uint x_l, uint y_l, uint x_u, uint y_u, bool mask_req, const pt_set& mask, double transparency_ratio){

    assert(space != NULL);
    assert(obj.is_solid());

    uint ny_area_pxs = y_u - y_l + 1;
    uint nx_area_pxs = x_u - x_l + 1;

    Color cur_col = obj.solid_col();
    cur_col.a(cur_col.a() * transparency_ratio);

    std::vector<Pixel> pixs_to_draw(nx_area_pxs * ny_area_pxs);

    for(uint n_row = 0; n_row < ny_area_pxs; n_row++){
        for(uint n_col = 0; n_col < nx_area_pxs; n_col++){
            if(!mask_req || mask.count({n_row, n_col})){

                pixs_to_draw[n_row * nx_area_pxs + n_col] = Pixel(x_l + n_col, y_l + n_row, cur_col);
            }
        }
    }
    space->drawPixels(pixs_to_draw);

    return;
}
//----------------------------------------------------------------------------------------//
