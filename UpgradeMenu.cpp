#include "UpgradeMenu.h"
#include "Button.h"
#include "Player.h"
#include "Game.h"
#include "Globals.h"
#include "Input.h"

UpgradeMenu::UpgradeMenu(ALLEGRO_BITMAP *buffer)
{
    upgradeMenu = al_load_bitmap ("Upgrade.bmp");
    font=al_load_bitmap_font("a4_font.tga");
    Init(buffer);
}

UpgradeMenu::~UpgradeMenu()
{
    al_destroy_bitmap(upgradeMenu);
    al_destroy_font(font);
}
 
void UpgradeMenu::Draw(ALLEGRO_BITMAP *buffer)
{
    Player &P = *Game::GetInstance()->GetPlayer();
    int rate = P.GetWeaponProperties(_Gun).GetFireRate();
    int clip = P.GetWeaponProperties(_Gun).GetClipSize();
    int range = P.GetWeaponProperties(_Gun).GetRange();
    int health = P.GetHealth();
    int money = P.GetMoney();
    WeaponProperties nuke = P.GetWeaponProperties(_Nuke);
    WeaponProperties wideShot = P.GetWeaponProperties(_WideShot);
    WeaponProperties grenade = P.GetWeaponProperties(_Grenade);
    WeaponProperties explodingShot = P.GetWeaponProperties(_ExplodingShot);
    WeaponProperties mine = P.GetWeaponProperties(_Mine);
    WeaponProperties wallBreaker = P.GetWeaponProperties(_WallBreaker);
    
    al_set_target_bitmap(buffer);
    al_draw_bitmap(upgradeMenu,0,0,0);
    
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-425, -1, "Current");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-425, -1, "Cost");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-425, -1, "Cost");
    al_draw_text(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-425, -1, "Owned");
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-392, -1, "%d", health);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-392, -1, "%d", 100+P.GetAddedHealth()/4);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-342, -1, "%d", rate);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-342, -1, "%d", 500*(11-rate)*(11-rate));
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-292, -1, "%d", clip);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-292, -1, "%d", 10*clip);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-350, SCREEN_Y-242, -1, "%d", range);
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-400, SCREEN_Y-242, -1, "%d", 100*(range/BOX_PIXEL_WIDTH));
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-392, -1, "%d", nuke.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-392, -1, "%d", nuke.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-342, -1, "%d", wideShot.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-342, -1, "%d", wideShot.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-292, -1, "%d", explodingShot.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-292, -1, "%d", explodingShot.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-242, -1, "%d", wallBreaker.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-242, -1, "%d", wallBreaker.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-192, -1, "%d", mine.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-192, -1, "%d", mine.GetCost());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-50, SCREEN_Y-142, -1, "%d", grenade.GetWeaponQuantity());
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-100, SCREEN_Y-142, -1, "%d", grenade.GetCost());
       
    al_draw_textf(font, al_map_rgb(255,255,255), SCREEN_X-500, SCREEN_Y-450, -1, "Money: %d", money);
    
    buttonManager.Update();
    buttonManager.Render(buffer);
    al_flip_display();
}

void UpgradeMenu::Init(ALLEGRO_BITMAP *buffer)
{
    Button *health = new Button();
    health->SetCaption("Add Health (H)");
    health->SetSize(100, 30);
    health->Create();
    health->OnClick = UpgradeMenu::Health;
    health->SetPosition(buffer, -500, -375);
    buttonManager.AddButton(health);
    Button *rate = new Button();
    rate->SetCaption("Fire Rate (F)");
    rate->SetSize(100, 30);
    rate->Create();
    rate->OnClick = UpgradeMenu::FireRate;
    rate->SetPosition(buffer, -500, -325);
    buttonManager.AddButton(rate);
    Button *clip = new Button();
    clip->SetCaption("Larger Clip (C)");
    clip->SetSize(100, 30);
    clip->Create();
    clip->OnClick = UpgradeMenu::ClipSize;
    clip->SetPosition(buffer, -500, -275);
    buttonManager.AddButton(clip);
    Button *range = new Button();
    range->SetCaption("Increase Range (R)");
    range->SetSize(100, 30);
    range->Create();
    range->OnClick = UpgradeMenu::Range;
    range->SetPosition(buffer, -500, -225);
    buttonManager.AddButton(range);
    Button *nuke = new Button();
    nuke->SetCaption("Buy Nuke (N)");
    nuke->SetSize(100, 30);
    nuke->Create();
    nuke->OnClick = UpgradeMenu::Nuke;
    nuke->SetPosition(buffer, -200, -375);
    buttonManager.AddButton(nuke);
    Button *wide = new Button();
    wide->SetCaption("Wider Shots (W)");
    wide->SetSize(100, 30);
    wide->Create();
    wide->OnClick = UpgradeMenu::WideShot;
    wide->SetPosition(buffer, -200, -325);
    buttonManager.AddButton(wide);
    Button *explode = new Button();
    explode->SetCaption("Exploding Shots (E)");
    explode->SetSize(100, 30);
    explode->Create();
    explode->OnClick = UpgradeMenu::ExplodingShot;
    explode->SetPosition(buffer, -200, -275);
    buttonManager.AddButton(explode);
    Button *walls = new Button();
    walls->SetCaption("Buy WallBreaker (S)");
    walls->SetSize(100, 30);
    walls->Create();
    walls->OnClick = UpgradeMenu::WallBreaker;
    walls->SetPosition(buffer, -200, -225);
    buttonManager.AddButton(walls);
    Button *mine = new Button();
    mine->SetCaption("Buy Mine (M)");
    mine->SetSize(100, 30);
    mine->Create();
    mine->OnClick = UpgradeMenu::Mine;
    mine->SetPosition(buffer, -200, -175);
    buttonManager.AddButton(mine);
    Button *grenade = new Button();
    grenade->SetCaption("Buy Grenade (G)");
    grenade->SetSize(100, 30);
    grenade->Create();
    grenade->OnClick = UpgradeMenu::Grenade;
    grenade->SetPosition(buffer, -200, -125);
    buttonManager.AddButton(grenade);
    Button *resume = new Button();
    resume->SetCaption("Resume (U)");
    resume->SetSize(100, 30);
    resume->Create();
    resume->OnClick = UpgradeMenu::Resume;
    resume->SetPosition(buffer, -450, -125);
    buttonManager.AddButton(resume);
}

ButtonManager &UpgradeMenu::GetButtonManager()
{
    return buttonManager;
}

void UpgradeMenu::Health(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_H);
}

void UpgradeMenu::FireRate(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_F);
}

void UpgradeMenu::ClipSize(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_C);
}

void UpgradeMenu::Range(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_R);
}

void UpgradeMenu::Nuke(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_N);
}

void UpgradeMenu::WideShot(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_W);
}

void UpgradeMenu::ExplodingShot(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_E);
}

void UpgradeMenu::WallBreaker(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_S);
}

void UpgradeMenu::Mine(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_M);
}

void UpgradeMenu::Grenade(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_G);
}

void UpgradeMenu::Resume(Button* object, void* data)
{
    Input::GetInstance()->ForcePressed(ALLEGRO_KEY_U);
}
