#ifndef GL_WRAPPER
#define GL_WRAPPER

#define SFML_LIB 0
#define QT_LIB   1

#ifndef ACTIVE_GRAPHIC_LIB
#define ACTIVE_GRAPHIC_LIB SFML_LIB
#endif

//#if ACTIVE_GRAPHIC_LIB == SFML_LIB
    #include <SFML/Graphics.hpp>
    #include <SFML/Graphics/Vertex.hpp>


//#elif ACTIVE_GRAPHIC_LIB == QT_LIB
//    #include <QtWidgets>
//#endif

// TODO: перегрузка + для даблов
class Color{
private:
    uint8_t r_, g_, b_, a_;
public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color(uint8_t r, uint8_t g, uint8_t b);
    
    uint8_t r() const { return r_; }
    uint8_t g() const { return g_; }
    uint8_t b() const { return b_; }
    uint8_t a() const { return a_; }

    void    r(uint8_t v) { r_ = v; }
    void    g(uint8_t v) { g_ = v; }
    void    b(uint8_t v) { b_ = v; }
    void    a(uint8_t v) { a_ = v; }

    //operator double() const;

    void  operator +=(const Color& col2);
    void  operator *=(const Color& col2);
    void  operator *=(double ratio);
    void  operator -=(const Color& col2);

    Color operator +(const Color& col2) const;
    Color operator *(const Color& col2) const;
    Color operator *(double ratio) const;
    Color operator -(const Color& col2) const;
};
//----------------------------------------------------------------------------------------//

class myButton{

private:
    uint x_upper_pix_, x_lower_pix_;
    uint y_upper_pix_, y_lower_pix_;

    Color col_;

public:

    myButton(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix, Color col);

    uint x_lower_pix() const { return x_lower_pix_; }
    uint x_upper_pix() const { return x_upper_pix_; }
    uint y_lower_pix() const { return y_lower_pix_; }
    uint y_upper_pix() const { return y_upper_pix_; }

    Color col() const { return col_; }
};

int  CheckCoordInButton(const myButton& but, uint x, uint y);
//----------------------------------------------------------------------------------------//

class GraphicSpace{

private:

//#if ACTIVE_GRAPHIC_LIB == SFML_LIB
    sf::RenderWindow window_;
//#elif ACTIVE_GRAPHIC_LIB == QT_LIB
//    QWidget wgt;    
//#endif

protected:

public:
    GraphicSpace(uint x_pixels, uint y_pixels);

    virtual void MouseButtonPressHandler(uint x_pos, uint y_pos){}
    virtual void CloseButtonPressHandler(){}
    virtual void Update(){}

    void Show();
    void Close();
    void Clear(Color col = Color(255, 255, 255, 255));
    void Init();

    void DrawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col = Color(0, 0, 0, 255));
    void DrawPixel(uint x_pix, uint y_pix, Color col = Color(0, 0, 0, 255));

    uint sizeX() const { return window_.getSize().x; }
    uint sizeY() const { return window_.getSize().y; }
    
    void Draw(const myButton& butt);
};
//----------------------------------------------------------------------------------------//

#endif // GL_WRAPPER
