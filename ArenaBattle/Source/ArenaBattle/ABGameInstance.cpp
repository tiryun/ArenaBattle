// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance() //프로젝트 실행 시 CDO를 제작하며 호출 / 게임 실행 시, CDO를 복제하여 생성
{
	AB_LOG(Warning, TEXT("Constructor Call Start"));

	//생성자에서 CDO를 만들 때만 사용되는 구문, 한 클래스당 CDO와 그 정보가 담긴 UClass가 같이 만들어진다
	WebConnect = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnect")); //이 구문을 통해 ABGameInstance의 CDO와 WebConnection의 CDO가 연결됨(붙어벌임) -> 게임 실행 시 CDO가 복제될 때 같이 딸려 생성됨

	AB_LOG(Warning, TEXT("Constructor Call End"));
} //그러니까, 현재 이 생성자에서는 ABGameInstance의 CDO와 WebConnect의 CDO가 묶여 생성되는 것


void UABGameInstance::Init() //게임 실행 시 가장 먼저 호출됨
{
	//Super::Init();
	//AB_LOG_CALLONLY(Warning);

	//WebConnect2 = NewObject<UWebConnection>(this); //this를 넣어줌, this 즉 나에게 소속되게(차일드로) 이 오브젝트를 생성함. 나를 생성시킬 때 나의 부모격 오브젝트는 GetOuter()로 불러올 수 있다.
	//AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnect2->GetOuter()->GetClass()->GetFullName());

	////GetWorld()를 통해 월드에 배치된 모든 컨텐츠를 검색 가능
	//UWorld* CurrentWorld = GetWorld();
	//for (const auto& Entry : FActorRange(CurrentWorld))
	//{
	//	AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
	//	TArray<UObject* > Components;
	//	Entry->GetDefaultSubobjects(Components);
	//	for (const auto& CEntry : Components)
	//	{
	//		AB_LOG(Warning, TEXT(" -- Component : %s"), *CEntry->GetName());
	//	}
	//}

	////특정 속성의 액터만 추출 가능
	//for (TActorIterator<AStaticMeshActor> It(CurrentWorld); It; ++It) //TObjectIterator이렇것도 있어!

	//{
	//	AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
	//}

	//유니크
	// 1단계
	// 땅은 힙, 뉴 하면 주소를 부여받음
	AB_LOG(Warning, TEXT("****** 1단계 ******"));
	FHouse* NewHouseAddress = new FHouse();
	AB_LOG(Warning, TEXT("집을 새로 지었습니다. 내집크기 : %d"), NewHouseAddress->Size);
	if (NewHouseAddress)
	{
		delete NewHouseAddress;
		AB_LOG(Warning, TEXT("내가 직접 집을 철거했습니다. 집크기 : %d"), NewHouseAddress->Size);
		NewHouseAddress = nullptr;
	}
	//딜리트 제대로 안하면 메모리 릭

	//->이걸 보완한 게 스마트포인터, 다시 사용되지 않는 포인터는 자동 삭제
	//유니크
	//공유(쉐어)
	//약(위크)


	// 2단계
	AB_LOG(Warning, TEXT("****** 2단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 100;
	AB_LOG(Warning, TEXT("집을 다시 지었습니다. 집크기 : %d"), NewHouseAddress->Size);
	{
		TUniquePtr<FHouse> MyHouseDeed = TUniquePtr<FHouse>(NewHouseAddress);
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("이 집은 제 단독소유 주택입니다. 내집크기 : %d"), MyHouseDeed->Size);
		}

		//TUniquePtr<FHouse> FriendsHouseDeed = MyHouseDeed;  // 컴파일 에러! 단독 소유만 가능, 소유를 기준으로 메모리 해제를 체크하기 때문에
		TUniquePtr<FHouse> FriendsHouseDeed = MoveTemp(MyHouseDeed); // 집은 그대로 두고 집주인만 변경 (기존 집에 대한 소유를 포기, 새 집으로 이주)
		if (!MyHouseDeed.IsValid()) //이 포인터를 안전하게 사용할 수 있는지 체크
		{
			AB_LOG(Warning, TEXT("친구에게 집을 팔았습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
		}
	}
	AB_LOG(Warning, TEXT("집문서가 사라져서 집은 자동으로 철거되었습니다. 집크기 : %d"));


	//쉐어
	// 3단계
	AB_LOG(Warning, TEXT("****** 3단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 150.0f;
	AB_LOG(Warning, TEXT("집을 또 다시 지었습니다. 집크기 : %d"), NewHouseAddress->Size);
	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress); // 만들어진 집을 차후에 등록
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("공동 소유 가능한 집이 되었습니다. 내집크기 : %d"), MyHouseDeed->Size);
			if (MyHouseDeed.IsUnique())
			{
				AB_LOG(Warning, TEXT("현재는 혼자 소유하고 있습니다. 내집크기 : %d"), MyHouseDeed->Size);
			}
		}

		TSharedPtr<FHouse> FriendsHouseDeed = MyHouseDeed;
		if (!FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("친구와 집을 나눠가지게 되었습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
		}

		MyHouseDeed.Reset(); // 내가 집 소유권을 포기함
		if (FriendsHouseDeed.IsUnique()) //몇명이 집 소유중? 
		{
			AB_LOG(Warning, TEXT("이제 친구만 집을 소유하고 있습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
		}

		AB_LOG(Warning, TEXT("집은 아직 그대로 있습니다. 집크기 : %d"), NewHouseAddress->Size);
	}

	AB_LOG(Warning, TEXT("집은 자동 철거되었습니다. 집크기 : %d"), NewHouseAddress->Size);


	// 4단계 순환참조 리핏
		AB_LOG(Warning, TEXT("****** 4단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 200.0f;
	AB_LOG(Warning, TEXT("집을 한번 더 다시 지었습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	FHouse* NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 250.0f;
	AB_LOG(Warning, TEXT("친구도 집을 직접 지었습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("내 집은 내가 소유합니다. 내집크기 : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("친구 집은 친구가 소유합니다. 친구집크기 : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("친구 집을 공동 소유하고 문서를 내 집에 보관합니다. 친구집크기 : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->OthersDeed = MyHouseDeed;
		AB_LOG(Warning, TEXT("친구도 내 집을 공동 소유하고 문서를 자기 집에 보관합니다. 내집크기 : %d"), FriendsHouseDeed->OthersDeed->Size);
	}

	AB_LOG(Warning, TEXT("집문서가 사라져도 내가 지은 집이 자동 철거되지 않습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("친구가 지은 집도 자동 철거되지 않습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	NewHouseAddress->OthersDeed.Reset();
	AB_LOG(Warning, TEXT("친구가 지은 집을 수동으로 철거했습니다. 집주소가 남아있어서 다행입니다. 두번째집크기 : %d"), NewHouseAddress2->Size);
	AB_LOG(Warning, TEXT("이제서야 내가 지은 집도 자동 철거됩니다. 첫번째집크기 : %d"), NewHouseAddress->Size);


	// 5단계 약, 능력치 밸런스 가장중요
	AB_LOG(Warning, TEXT("****** 5단계 ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 300.0f;
	AB_LOG(Warning, TEXT("이제 마지막으로 집을 짓습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 350.0f;
	AB_LOG(Warning, TEXT("친구도 집을 다시 지었습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("내 집은 내가 소유합니다. 내집크기 : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("친구 집은 친구가 소유합니다. 친구집크기 : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("친구 집을 공동 소유하고 문서를 내 집에 보관합니다. 친구집크기 : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->AccessHouse = MyHouseDeed;
		AB_LOG(Warning, TEXT("친구가 내 집 정보를 열람합니다. 내집크기 : %d"), FriendsHouseDeed->AccessHouse.Pin()->Size);
	}

	AB_LOG(Warning, TEXT("내가 지은 집은 자동 철거됩니다. 첫번째집크기 : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("친구가 지은 집도 자동 철거됩니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	AB_LOG(Warning, TEXT("****** 6단계 ******"));
	WebConnect2 = NewObject<UWebConnection>();
	WebConnect2->Host = TEXT("127.0.0.1");
	//WebConnectionNew->AddToRoot();
	WebConnect2->ConditionalBeginDestroy();
	//GetWorld()->ForceGarbageCollection(true);
	GetWorld()->GetTimerManager().SetTimer(ObjectCheckTimer, this, &UABGameInstance::CheckUObjectAlive, 1.0f, true);


	//UClass* ClassInfo1 = WebConnect->GetClass(); //CDO와 같이 생성된 CDO의 UClass에서 정보를 가져온다, 이 정보를 사용해서 현재 자신의 정보를 변경하는 등의 일이 가능
	//UClass* ClassInfo2 = UWebConnection::StaticClass(); //이 경우에도 위와 동일하게 CDO와 같이 생성된 UClass를 가리킴

	//if(ClassInfo1 == ClassInfo2)
	//	AB_LOG(Warning, TEXT("ClassInfo1 == ClassInfo2"));

	//for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It) //클래스 정보 내의 모든 속성을 검사
	//{
	//	AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName()); //속성의 이름과 그 타입 출력
	//	UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
	//	if (StrProp) //속성에 내용이 들어가 있다면,
	//	{
	//		AB_LOG(Warning, TEXT("Value = %s"), 
	//			*StrProp->GetPropertyValue_InContainer(WebConnect)); //해당 내용의 값을 가져와 출력 
	//			//가져오는 것 뿐만 아닌 값을 넣어줄 수도 있으며, 이것은 기본 인스턴스 오브젝트이기 때문에 이를 참조하는 모든 오브젝트의 값을 변경 가능
	//	}
	//}

	//for (const auto& Entry : ClassInfo1->NativeFunctionLookupTable)
	//{
	//	AB_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
	//	UFunction* Func1 = ClassInfo1->FindFunctionByName(Entry.Name);
	//	if (Func1->ParmsSize == 0)
	//	{
	//		WebConnect->ProcessEvent(Func1, NULL);
	//	}
	//}
}

void UABGameInstance::CheckUObjectAlive()
{
	if (!WebConnect2)
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 널입니다."));
		return;
	}

	if (!WebConnect2->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 유효하지 않습니다."));
		return;
	}

	AB_LOG(Warning, TEXT("언리얼오브젝트가 아직 살아있습니다. : %s"), *WebConnect2->Host);
}


