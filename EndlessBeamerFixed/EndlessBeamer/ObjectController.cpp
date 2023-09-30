#include "ObjectController.h"

const float ObstructSize = 5.f;
const float BossSize = 8.5f;
const float ObstructHitEndPosZ = 10.f;

ObjectController::ObjectController()
{
    playerPoint = 0;
    playerBeamPoint = 0;
    plusTime = false;
    killed = 0;
}

ObjectController::~ObjectController()
{
}

void ObjectController::Update(float deltaTime)
{
    object[playerBeamPoint]->SetPlayerpos(object[playerPoint]->PosGetter());
    plusTime = false;
    killed = 0;
    for (auto ptr : object)
    {
        ptr->Update(deltaTime);
    }
    HitChecker(deltaTime);
    
}

void ObjectController::DrawAll()
{
    for (auto ptr : object)
    {
        ptr->Draw();
    }
}

void ObjectController::Entry(Object* newObj)
{
    object.emplace_back(newObj);
}

void ObjectController::Delete()
{
    std::vector<Object*>deleteObj;
    for (auto ptr : object)
    {
        if (ptr->IsEnd())
        {
            if (ptr->PosGetter().z > ObstructHitEndPosZ&&(ptr->TypeGetter()==METEOR|| ptr->TypeGetter() == NEEDLE))
            {
                Entry(new Exprosion(ptr->PosGetter()));
            }
            deleteObj.emplace_back(ptr);
        }
    }
    for (auto ptr : deleteObj)
    {
        auto iter = std::find(object.begin(), object.end(), ptr);
        if (iter != object.end())
        {
            std::iter_swap(iter, object.end() - 1);
            object.pop_back();
        }
    }
}

void ObjectController::ClearAll()
{
    object.clear();
}

void ObjectController::HitChecker(float deltaTime)
{
    for (auto ptr : object)
    {
        if (ptr->TypeGetter() == NEEDLE || ptr->TypeGetter() == METEOR||ptr->TypeGetter()==BOSS)
        {
            float ratio = ptr->PosGetter().z / object[playerBeamPoint]->PosGetter().z;
            float hitPointX = object[playerPoint]->PosGetter().x + ((object[playerBeamPoint]->PosGetter().x - object[playerPoint]->PosGetter().x) * ratio);
            float hitPointY = object[playerPoint]->PosGetter().y + ((object[playerBeamPoint]->PosGetter().y - object[playerPoint]->PosGetter().y) * ratio);
            VECTOR hitPos = VGet(hitPointX, hitPointY, ptr->PosGetter().z);
            float dis = pow((ptr->PosGetter().x - hitPos.x), 2.f) + pow((ptr->PosGetter().y - hitPos.y), 2.f);
            dis = sqrt(dis);
            if (ptr->TypeGetter() != BOSS)
            {
                if (dis<ObstructSize && ptr->PosGetter().z>ObstructHitEndPosZ)
                {
                    ptr->GivenDmg(deltaTime);
                    Entry(new Particle(ptr->PosGetter()));
                    if (ptr->IsEnd())
                    {
                        if (ptr->TypeGetter() == METEOR)
                        {
                            plusTime = true;
                            //‚±‚±‚É+10.0s‚Ì•`‰æŠJŽn‚ð“ü‚ê‚é
                        }
                        killed++;
                    }
                }
            }
            else
            {
                if (dis <= BossSize)
                {
                    ptr->GivenDmg(deltaTime);
                    Entry(new Particle(ptr->PosGetter()));
                }
                if (ptr->IsEnd())
                {
                    killed++;
                }
            }
            
        }
    }
}

void ObjectController::SetPlayerAndPlayerBeam()
{
    for (int i = 0; i < object.size(); i++)
    {
        if (object[i]->TypeGetter() == PLAYER)
        {
            playerPoint = i;
        }
        if (object[i]->TypeGetter() == PLAYER_BEAM)
        {
            playerBeamPoint = i;
        }
    }
}

int ObjectController::GetSize()
{
    return object.size();
}

bool ObjectController::PlusTimeFlag()
{
    return plusTime;
}

int ObjectController::KilledNum()
{
    return killed;
}

int ObjectController::TypeObjetNumGetter(ObjectType objName)
{
    int num = 0;
    for (auto ptr : object)
    {
        if (ptr->TypeGetter() == objName)
        {
            num++;
        }
    }

    return num;
}

VECTOR ObjectController::PlayerPosGetter()
{
    return object[playerPoint]->PosGetter();
}

bool ObjectController::ChangeBoss()
{
    for (auto ptr : object)
    {
        if (ptr->TypeGetter() == NEEDLE || ptr->TypeGetter() == METEOR)
        {
            ptr->SetDead();
            Entry(new Exprosion(ptr->PosGetter()));
        }
    }
    for (auto ptr : object)
    {
        if (ptr->TypeGetter() == NEEDLE || ptr->TypeGetter() == METEOR || ptr->TypeGetter() == EXPROSION)
        {
            return false;
        }
    }

    return true;
}

