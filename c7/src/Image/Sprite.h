#ifndef BAKUDAN_IMAGE_SPRITE_H_
#define BAKUDAN_IMAGE_SPRITE_H_
#include "Rect.h"

class File;
class Point;
class Size;
namespace Game { namespace Event { class Move; } }
namespace GameLib { class Texture; }

namespace Image
{

class Sprite 
{
private:
    const Size* size_;
    const Size* cell_size_;
    const unsigned* data_;
    const int cells_per_column_;
    const int cells_per_row_;
    GameLib::Texture* texture_;
    const Size* texture_size_;

public:
    Sprite(const File& image_file, int column_count, int row_count);
    ~Sprite();
    const Size& size() const;
    const Size& cell_size() const;
    const unsigned* data() const;
    int cells_per_column() const;
    void copy(int cell_index, const Rect< double >& rect) const;
    void copy(int cell_index, const Point& point) const;
    void copy(int cell_index, double left, double top) const;
    void copy(  int cell_index,
                const Point& point,
                const Size& size,
                unsigned* vram) const;
    void copy(  int cell_index,
                const Game::Event::Move& event,
                const Size& size,
                unsigned* vram) const;
    void copy_alpha_blend(  int cell_index,
                            double alpha,
                            const Point& point,
                            const Size& size,
                            unsigned* vram) const;
    void copy_alpha_blend(  int cell_index,
                            const Point& point,
                            const Size& size,
                            unsigned* vram) const;
    void copy_alpha_blend(  int cell_index,
                            const Game::Event::Move& event,
                            const Size& size,
                            unsigned* vram) const;
    void copy_alpha_blend(  int cell_index,
                            double alpha,
                            const Game::Event::Move& event,
                            const Size& size,
                            unsigned* vram) const;
    int cell_width() const;
    int cell_height() const;
    void set_inner_area_of(int index, Rect< double >* rect) const;
};

} // namespace Image

#endif
