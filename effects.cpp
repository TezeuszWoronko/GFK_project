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


