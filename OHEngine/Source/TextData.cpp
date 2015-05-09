#include "TextData.h"

TextData::TextData(void)
{
    this->textMesh = TexturedModel();
    this->text = "nothing";
    this->color = Color();
    this->size = 1.f;
    this->position = Vector2(1.f, 1.f);
}

TextData::TextData(TexturedModel textMesh, std::string text, Color color, float size, Vector2 position)
{
    this->textMesh = textMesh;
    this->text = text;
    this->color = color;
    this->size = size;
    this->position = position;
}

TextData::~TextData(void)
{

}

TexturedModel TextData::getTextMesh(void)
{
    return textMesh;
}

void TextData::setTextMesh(TexturedModel textMesh)
{
    this->textMesh = textMesh;
}

std::string TextData::getText(void)
{
    return text;
}

void TextData::setText(std::string text)
{
    this->text = text;
}

Color TextData::getColor(void)
{
    return color;
}

void TextData::setColor(Color color)
{
    this->color = color;
}

float TextData::getSize(void)
{
    return size;
}

void TextData::setSize(float size)
{
    this->size = size;
}

Vector2 TextData::getPosition(void)
{
    return position;
}

void TextData::setPosition(Vector2 position)
{
    this->position = position;
}