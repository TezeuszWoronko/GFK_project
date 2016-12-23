#include "effects.h"

void defaultOperation(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    return;
}

void enterLeft(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    unsigned char r, g, b;
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
    for(unsigned i = 0; i < image1->GetWidth(); i++) {
        for(unsigned j = 0; j < image1->GetHeight(); j++) {
            if(i > border)
                result->SetRGB(i,j,image1->GetRed(i,j),image1->GetGreen(i,j),image1->GetBlue(i,j));
            else
                result->SetRGB(i,j,image2->GetRed(i+step,j),image2->GetGreen(i+step,j),image2->GetBlue(i+step,j));
        }    
    }
    return;
}

void enterRight(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    unsigned char r, g, b;
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
    for(unsigned i = 0; i < image1->GetWidth(); i++) {
        for(unsigned j = 0; j < image1->GetHeight(); j++) {
            if(i < border)
                result->SetRGB(i,j,image1->GetRed(i,j),image1->GetGreen(i,j),image1->GetBlue(i,j));
            else
                result->SetRGB(i,j,image2->GetRed(i-step,j),image2->GetGreen(i-step,j),image2->GetBlue(i-step,j));
        }    
    }
    return;
}

void enterUp(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    unsigned char r, g, b;
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
    for(unsigned i = 0; i < image1->GetWidth(); i++) {
        for(unsigned j = 0; j < image1->GetHeight(); j++) {
            if(j > border)
                result->SetRGB(i,j,image1->GetRed(i,j),image1->GetGreen(i,j),image1->GetBlue(i,j));
            else
                result->SetRGB(i,j,image2->GetRed(i,j+step),image2->GetGreen(i,j+step),image2->GetBlue(i,j+step));
        }    
    }
    return;
}

void enterDown(wxImage* result, wxImage* image1, wxImage* image2, int i, int n) {
    unsigned char r, g, b;
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
    for(unsigned i = 0; i < image1->GetWidth(); i++) {
        for(unsigned j = 0; j < image1->GetHeight(); j++) {
            if(j < border)
                result->SetRGB(i,j,image1->GetRed(i,j),image1->GetGreen(i,j),image1->GetBlue(i,j));
            else
                result->SetRGB(i,j,image2->GetRed(i,j-step),image2->GetGreen(i,j-step),image2->GetBlue(i,j-step));
        }    
    }
    return;
}


