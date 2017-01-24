#include "effects.h"

void defaultOperation(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    return;
}

void enterLeft(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {    
    float border = ((float)i)/((float)(n-1));
    border*= image1->GetWidth();
    if(border < 0)
        border = 0;
    if(border > image1->GetWidth())
        border = image1->GetWidth();
    float step = image1->GetWidth() - 1 - border;
    if(step < 0)
        step = 0;
    if(step > image1->GetWidth())
        step = image1->GetWidth()-1;
    unsigned x, y; 
    #pragma omp parallel for private(y)
    for(x = 0; x < image1->GetWidth(); x++) {    
        for(y = 0; y < image1->GetHeight(); y++) {
            if(x > border)
                result->SetRGB(x,y,image1->GetRed(x,y),image1->GetGreen(x,y),image1->GetBlue(x,y));
            else
                result->SetRGB(x,y,image2->GetRed(x+step,y),image2->GetGreen(x+step,y),image2->GetBlue(x+step,y));
        }    
    }
    return;
}

void enterRight(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    float border = 1.0 - ((float)i)/((float)(n-1));
    border*= image1->GetWidth();
    if(border < 0)
        border = 0;
    if(border > image1->GetWidth())
        border = image1->GetWidth() - 1;
    float step = border;
    if(step < 0)
        step = 0;
    if(step > image1->GetWidth())
        step = image1->GetWidth()-1;
    unsigned x, y; 
    #pragma omp parallel for private(y)
    for(x = 0; x < image1->GetWidth(); x++) {
        for(y = 0; y < image1->GetHeight(); y++) {
            if(x < border)
                result->SetRGB(x,y,image1->GetRed(x,y),image1->GetGreen(x,y),image1->GetBlue(x,y));
            else
                result->SetRGB(x,y,image2->GetRed(x-step,y),image2->GetGreen(x-step,y),image2->GetBlue(x-step,y));
        }    
    }
    return;
}

void enterUp(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    float border = ((float)i)/((float)(n-1));
    border*= image1->GetHeight();
    if(border < 0)
        border = 0;
    if(border > image1->GetHeight())
        border = image1->GetHeight();
    float step = image1->GetHeight() - 1 - border;
    if(step < 0)
        step = 0;
    if(step > image1->GetHeight())
        step = image1->GetHeight()-1;
    unsigned x, y; 
    #pragma omp parallel for private(y)
    for(x = 0; x < image1->GetWidth(); x++) {
        for(y = 0; y < image1->GetHeight(); y++) {
            if(y > border)
                result->SetRGB(x,y,image1->GetRed(x,y),image1->GetGreen(x,y),image1->GetBlue(x,y));
            else
                result->SetRGB(x,y,image2->GetRed(x,y+step),image2->GetGreen(x,y+step),image2->GetBlue(x,y+step));
        }    
    }
    return;
}

void enterDown(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    float border = 1.0 - ((float)i)/((float)(n-1));
    border*= image1->GetHeight();
    if(border < 0)
        border = 0;
    if(border > image1->GetHeight())
        border = image1->GetHeight() - 1;
    float step = border;
    if(step < 0)
        step = 0;
    if(step > image1->GetHeight())
        step = image1->GetHeight()-1;
    unsigned x, y; 
    #pragma omp parallel for private(y)
    for(x = 0; x < image1->GetWidth(); x++) {
        for(y = 0; y < image1->GetHeight(); y++) {
            if(y < border)
                result->SetRGB(x,y,image1->GetRed(x,y),image1->GetGreen(x,y),image1->GetBlue(x,y));
            else
                result->SetRGB(x,y,image2->GetRed(x,y-step),image2->GetGreen(x,y-step),image2->GetBlue(x,y-step));
        }    
    }
    return;
}


void transition(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    float alpha = ((float)i)/((float)(n-1));
    unsigned x, y; 
    #pragma omp parallel for private(y)
    for(x = 0; x < image1->GetWidth(); x++) {
        for(y = 0; y < image1->GetHeight(); y++) {
            result->SetRGB(x, y, alpha*(image1->GetRed(x,y)) + (1-alpha)*(image2->GetRed(x,y)), alpha*(image1->GetGreen(x,y)) + (1-alpha)*(image2->GetGreen(x,y)), alpha*(image1->GetBlue(x,y)) + (1-alpha)*(image2->GetBlue(x,y)));
        }
    }
    return;
}

void horizontalFlip(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    int x, y, xPrev=0, yPrev =0;
    float b, borderVertical, step = 0;
    wxImage* currentImage = image1;
    float position = (float)i/(float)(n-1);
    if(position < 0.5){currentImage = image1;}
    else{currentImage = image2;}
    float borderHorizontal = i*((float)currentImage->GetWidth())/((float)(n-1));
    float a =  fabs(((float)currentImage->GetWidth() - 2*borderHorizontal)/ ((float)currentImage->GetWidth()));
    if(position > 0.5){borderVertical = 0.1*(currentImage->GetHeight())*(1-position);}
    else{borderVertical = 0.1*(currentImage->GetHeight())*position;}
    float h = ((float)2*borderVertical)/(float)(currentImage->GetWidth() - 2*borderHorizontal);
    if(position < 0.5){b = ((float)currentImage->GetHeight() + 2*borderVertical)/ ((float)currentImage->GetHeight());}
    else{b = ((float)currentImage->GetHeight() - 2*borderVertical)/ ((float)currentImage->GetHeight());}
    unsigned j, k; 
    for(j = 0; j < currentImage->GetWidth(); j++) { 
        for(k = 0; k < currentImage->GetHeight(); k++) {
            if(position < 0.5){x = (int)(a*j) + borderHorizontal;}
            else{x = (int)(a*j) + currentImage->GetWidth() - borderHorizontal;}
            if(position < 0.5){y = -borderVertical + (int)step + (int)(b*k);}
            else{y = borderVertical - (int)step + (int)(b*k);}
            if(x != xPrev && position < 0.5){step += h;}
            else if(x != xPrev && position >= 0.5){step -= h;}
            xPrev = x;
            yPrev = y;
            if(x >= 0 && x < currentImage->GetWidth() && y >= 0 && y < currentImage->GetHeight()){result->SetRGB(x,y,currentImage->GetRed(j,k),currentImage->GetGreen(j,k),currentImage->GetBlue(j,k));}
            if(y < currentImage->GetHeight() - 2){
                if(x >= 0 && x < currentImage->GetWidth() && y >= 0 && y < currentImage->GetHeight()){result->SetRGB(x,y+1,currentImage->GetRed(j,k),currentImage->GetGreen(j,k),currentImage->GetBlue(j,k));}
                if(x >= 0 && x < currentImage->GetWidth() && y >= 0 && y < currentImage->GetHeight()){result->SetRGB(x,y+2,currentImage->GetRed(j,k),currentImage->GetGreen(j,k),currentImage->GetBlue(j,k));}
            }
        }
        if(position < 0.5){b = ((float)currentImage->GetHeight() + 2*borderVertical - 2*((int)step))/ ((float)currentImage->GetHeight());}
        else{b = ((float)currentImage->GetHeight() - 2*borderVertical + 2*((int)step))/ ((float)currentImage->GetHeight());}
    }
    return;
    


}


void verticalFlip(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    int x, y, xPrev=0, yPrev =0;
    wxImage* currentImage = NULL;
    float borderHorizontal, step = 0, a;
    float position = (float)i/(float)(n-1);
    if(position < 0.5){currentImage = image1;}
    else{currentImage = image2;}
    float borderVertical = i*((float)currentImage->GetHeight())/((float)(n-1));
    float b =  fabs(((float)currentImage->GetHeight() - 2*borderVertical)/ ((float)currentImage->GetHeight()));
    if(position > 0.5){borderHorizontal = 0.1*(image1->GetWidth())*(1-position);}
    else{borderHorizontal = 0.1*(image1->GetWidth())*position;}
    float h = ((float)2*borderHorizontal)/(float)(currentImage->GetHeight() - 2*borderVertical);
    if(position < 0.5){a = ((float)currentImage->GetWidth() - 2*borderHorizontal)/ ((float)currentImage->GetWidth());}
    else{a = ((float)currentImage->GetWidth() + 2*borderHorizontal)/ ((float)currentImage->GetWidth());}
    unsigned j, k; 
    for(j = 0; j < currentImage->GetHeight(); ++j) {
        for(k = 0; k < currentImage->GetWidth(); ++k) {
            if(position < 0.5){y = (int)(b*j) + borderVertical;}
            else{y = (int)(b*j) + currentImage->GetHeight() - borderVertical;}
            if(position < 0.5){x = borderHorizontal - (int)step + (int)(a*k);}
            else{x = -borderHorizontal + (int)step + (int)(a*k);}
            if(y != yPrev && position < 0.5){step += h;}
            else if(y != yPrev && position >= 0.5){step -= h;}
            xPrev = x;
            yPrev = y;
            if(x >= 0 && x < currentImage->GetWidth() && y >= 0 && y < currentImage->GetHeight()){result->SetRGB(x,y,currentImage->GetRed(k,j),currentImage->GetGreen(k,j),currentImage->GetBlue(k,j));}
            if(x < currentImage->GetWidth() - 2){
                if(x >= 0 && x < currentImage->GetWidth() && y >= 0 && y < currentImage->GetHeight()){result->SetRGB(x+1,y,currentImage->GetRed(k,j),currentImage->GetGreen(k,j),currentImage->GetBlue(k,j));}
                if(x >= 0 && x < currentImage->GetWidth() && y >= 0 && y < currentImage->GetHeight()){result->SetRGB(x+2,y,currentImage->GetRed(k,j),currentImage->GetGreen(k,j),currentImage->GetBlue(k,j));}
            }
        }
        if(position < 0.5){a = ((float)currentImage->GetWidth() - 2*borderHorizontal + 2*((int)step))/ ((float)currentImage->GetWidth());}
        else{a = ((float)currentImage->GetWidth() + 2*borderHorizontal - 2*((int)step))/ ((float)currentImage->GetWidth());}
    }
    
    return;
}


int normRGB(int value){
    if(value<0)
            return 0;
    else if(value>255)
            return 255;
    else 
        return value;
}

void darkening(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    unsigned char r, g, b;
    float val = (((float)i)/((float)n)) * 255 * 2;
    float step = 1 / ((float) n) * 255 * 2;
    unsigned x, y; 
    
    for(x = 0; x < image1->GetWidth(); x++) {
        for(y = 0; y < image1->GetHeight(); y++) {
            if(val < 255){
                r = normRGB(image1->GetRed(x,y) - val);
                g = normRGB(image1->GetGreen(x,y) - val);
                b = normRGB(image1->GetBlue(x,y) - val);
            } else {
                float v2 = 255 - fmod(val, 255) - step;
                r = normRGB(image2->GetRed(x,y)-v2);
                g = normRGB(image2->GetGreen(x,y)-v2);
                b = normRGB(image2->GetBlue(x,y)-v2);
            }
            result->SetRGB(x,y,r,g,b);
        }    
    }    
    return;
}

void enterBox(wxImage* result, wxImage* image1, wxImage* image2, int i, int n){

    unsigned char r, g, b;
    float border = (((float)i)/((float)n)) + ( 1 / (float)n );
    
    int w1 = image1->GetWidth();
    int h1 = image1->GetHeight();    
    int w2 = border * image1->GetWidth();
    int h2 = border * image1->GetHeight();
    
    float x_ratio = w1/(float)w2 ;
    float y_ratio = h1/(float)h2 ;
    float px, py; 
    
    float x_start = w1/2 - w2/2;
    float y_start = h1/2 - h2/2;    
    
    unsigned x, y; 

    for(x= 0; x< w1; x++) {
        for(y = 0; y < h1; y++) {
            int r, g, b;
            r = image1->GetRed(x,y);
            g = image1->GetGreen(x,y);
            b = image1->GetBlue(x,y);
            
            if( x>= x_start && 
                x< x_start + w2 &&
                y >= y_start &&
                y < y_start + h2 ) {
                
                float small_x= x- x_start;
                float small_y = y - y_start;
                
                px = small_x*x_ratio ;
                py = small_y*y_ratio ;
                
                r = image2->GetRed(px, py);
                g = image2->GetGreen(px, py);
                b = image2->GetBlue(px, py);
                
            }
            
            result->SetRGB(x, y, r, g, b);
        }
    }
 
    return;
}

void exitBox(wxImage* result, wxImage* image1, wxImage* image2, int i, int n){
    unsigned char r, g, b;
    float border = 1 - (((float)i)/((float)n));
    
    int w1 = image1->GetWidth();
    int h1 = image1->GetHeight();    
    int w2 = border * image1->GetWidth();
    int h2 = border * image1->GetHeight();
    
    float x_ratio = w1/(double)w2 ;
    float y_ratio = h1/(double)h2 ;
    float px, py; 

    float x_start = w1/2 - w2/2;
    float y_start = h1/2 - h2/2;    
    
    unsigned x, y; 

    for(x = 0; x < w1; x++) {
        for(y = 0; y < h1; y++) {
            int r, g, b;
            r = image1->GetRed(x,y);
            g = image1->GetGreen(x,y);
            b = image1->GetBlue(x,y);
            if( x >= x_start && 
                x < x_start + w2 &&
                y >= y_start &&
                y < y_start + h2 ) {
                
                float small_x = x - x_start;
                float small_y = y - y_start;
                
                px = small_x*x_ratio ;
                py = small_y*y_ratio ;
                
                r = image2->GetRed(px, py);
                g = image2->GetGreen(px, py);
                b = image2->GetBlue(px, py);
            }
            result->SetRGB(x, y, r, g, b);

        }
    }
    
    return;
}

void enterWindow(wxImage* result, wxImage* image1, wxImage* image2, int d, int n){
    unsigned char r, g, b;
    float border = 1 - ((2*(float)d)/((float)n-1));
    float bord = d;
    
    int w1 = image1->GetWidth();
    int h1 = image1->GetHeight();    
    int w2 = border * image1->GetWidth();
    int h2 = h1;

    float x_start = w1 - w2;
    float y_start = 0;  
    
    float x_ratio = w1/(float)w2 ;
    float y_ratio = h1/(float)h2 ;
    int px, py; 
    
    if(bord < n/2){
        unsigned i, j; 

        for (i=0; i<h1; i++) {
            for (j=0; j<w2; j++) {
                float skok;
                skok = (1-(float)j / (float)w2) * 2 * bord * (h1/(float)n);
    
                int r,g,b;
                h2 = (h1 - skok);
                y_ratio = (float)h1 / (float)h2;
                px = floor(j * x_ratio); 
                py = floor((i - (skok/2)) * y_ratio);
                if(px >= 0 && px < w1 && py >= 0 && py < h1){
                    r = image1->GetRed(px, py);
                    g = image1->GetGreen(px, py);
                    b = image1->GetBlue(px, py);
                } else {
                    r = g = b = 0;    
                }
    
                if(j+x_start >= 0 && j+x_start < w1 && i+y_start >= 0 && i+y_start < h1){
                    result->SetRGB(j+x_start, i+y_start, r, g, b) ;
                }
            }
        }  
    }
    
    float border2 ;
    float b2;

    if( n%2 == 0 ){
        d = d+1;
        b2 = d - n/2;
        border2 = ((2*(float)b2)/((float)n));
    } else {
        b2 = d - n/2;
        border2 = ((2*(float)b2)/((float)n-1));
    }
    
    x_start = 0;
    w2 = border2 * image1->GetWidth();
    x_ratio = w1/(float)w2 ;
    
    
    
    if(d >= n/2){
        unsigned i, j; 

        for (i=0; i<h1; i++) {
            for (j=0; j<w2; j++) {
                float skok;
                skok = ((float)j / (float)w2) * 2 * (n/2-b2) * (h1/(float)n);
                int r,g,b;
                h2 = (h1 - skok);
                y_ratio = (float)h1 / (float)h2;
                px = floor(j * x_ratio); 
                py = floor((i - (skok/2)) * y_ratio);
                if(px >= 0 && px < w1 && py >= 0 && py < h1){
                    r = image2->GetRed(px, py);
                    g = image2->GetGreen(px, py);
                    b = image2->GetBlue(px, py);
                } else {
                    r = g = b = 0;    
                }
    
                if(j+x_start >= 0 && j+x_start < w1 && i+y_start >= 0 && i+y_start < h1){
                    result->SetRGB(j+x_start, i+y_start, r, g, b) ;
                }
            }
        }
    }
    return;
}






