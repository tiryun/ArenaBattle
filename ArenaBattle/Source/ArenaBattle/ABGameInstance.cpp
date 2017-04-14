// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance() //������Ʈ ���� �� CDO�� �����ϸ� ȣ�� / ���� ���� ��, CDO�� �����Ͽ� ����
{
	AB_LOG(Warning, TEXT("Constructor Call Start"));

	//�����ڿ��� CDO�� ���� ���� ���Ǵ� ����, �� Ŭ������ CDO�� �� ������ ��� UClass�� ���� ���������
	WebConnect = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnect")); //�� ������ ���� ABGameInstance�� CDO�� WebConnection�� CDO�� �����(�پ����) -> ���� ���� �� CDO�� ������ �� ���� ���� ������

	AB_LOG(Warning, TEXT("Constructor Call End"));
} //�׷��ϱ�, ���� �� �����ڿ����� ABGameInstance�� CDO�� WebConnect�� CDO�� ���� �����Ǵ� ��


void UABGameInstance::Init() //���� ���� �� ���� ���� ȣ���
{
	//Super::Init();
	//AB_LOG_CALLONLY(Warning);

	//WebConnect2 = NewObject<UWebConnection>(this); //this�� �־���, this �� ������ �Ҽӵǰ�(���ϵ��) �� ������Ʈ�� ������. ���� ������ų �� ���� �θ�� ������Ʈ�� GetOuter()�� �ҷ��� �� �ִ�.
	//AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnect2->GetOuter()->GetClass()->GetFullName());

	////GetWorld()�� ���� ���忡 ��ġ�� ��� �������� �˻� ����
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

	////Ư�� �Ӽ��� ���͸� ���� ����
	//for (TActorIterator<AStaticMeshActor> It(CurrentWorld); It; ++It) //TObjectIterator�̷��͵� �־�!

	//{
	//	AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
	//}

	//����ũ
	// 1�ܰ�
	// ���� ��, �� �ϸ� �ּҸ� �ο�����
	AB_LOG(Warning, TEXT("****** 1�ܰ� ******"));
	FHouse* NewHouseAddress = new FHouse();
	AB_LOG(Warning, TEXT("���� ���� �������ϴ�. ����ũ�� : %d"), NewHouseAddress->Size);
	if (NewHouseAddress)
	{
		delete NewHouseAddress;
		AB_LOG(Warning, TEXT("���� ���� ���� ö���߽��ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
		NewHouseAddress = nullptr;
	}
	//����Ʈ ����� ���ϸ� �޸� ��

	//->�̰� ������ �� ����Ʈ������, �ٽ� ������ �ʴ� �����ʹ� �ڵ� ����
	//����ũ
	//����(����)
	//��(��ũ)


	// 2�ܰ�
	AB_LOG(Warning, TEXT("****** 2�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 100;
	AB_LOG(Warning, TEXT("���� �ٽ� �������ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
	{
		TUniquePtr<FHouse> MyHouseDeed = TUniquePtr<FHouse>(NewHouseAddress);
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("�� ���� �� �ܵ����� �����Դϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
		}

		//TUniquePtr<FHouse> FriendsHouseDeed = MyHouseDeed;  // ������ ����! �ܵ� ������ ����, ������ �������� �޸� ������ üũ�ϱ� ������
		TUniquePtr<FHouse> FriendsHouseDeed = MoveTemp(MyHouseDeed); // ���� �״�� �ΰ� �����θ� ���� (���� ���� ���� ������ ����, �� ������ ����)
		if (!MyHouseDeed.IsValid()) //�� �����͸� �����ϰ� ����� �� �ִ��� üũ
		{
			AB_LOG(Warning, TEXT("ģ������ ���� �Ⱦҽ��ϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);
		}
	}
	AB_LOG(Warning, TEXT("�������� ������� ���� �ڵ����� ö�ŵǾ����ϴ�. ��ũ�� : %d"));


	//����
	// 3�ܰ�
	AB_LOG(Warning, TEXT("****** 3�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 150.0f;
	AB_LOG(Warning, TEXT("���� �� �ٽ� �������ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress); // ������� ���� ���Ŀ� ���
		if (MyHouseDeed.IsValid())
		{
			AB_LOG(Warning, TEXT("���� ���� ������ ���� �Ǿ����ϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
			if (MyHouseDeed.IsUnique())
			{
				AB_LOG(Warning, TEXT("����� ȥ�� �����ϰ� �ֽ��ϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
			}
		}

		TSharedPtr<FHouse> FriendsHouseDeed = MyHouseDeed;
		if (!FriendsHouseDeed.IsUnique())
		{
			AB_LOG(Warning, TEXT("ģ���� ���� ���������� �Ǿ����ϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);
		}

		MyHouseDeed.Reset(); // ���� �� �������� ������
		if (FriendsHouseDeed.IsUnique()) //����� �� ������? 
		{
			AB_LOG(Warning, TEXT("���� ģ���� ���� �����ϰ� �ֽ��ϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);
		}

		AB_LOG(Warning, TEXT("���� ���� �״�� �ֽ��ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);
	}

	AB_LOG(Warning, TEXT("���� �ڵ� ö�ŵǾ����ϴ�. ��ũ�� : %d"), NewHouseAddress->Size);


	// 4�ܰ� ��ȯ���� ����
		AB_LOG(Warning, TEXT("****** 4�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 200.0f;
	AB_LOG(Warning, TEXT("���� �ѹ� �� �ٽ� �������ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);

	FHouse* NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 250.0f;
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �������ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("�� ���� ���� �����մϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("ģ�� ���� ģ���� �����մϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("ģ�� ���� ���� �����ϰ� ������ �� ���� �����մϴ�. ģ����ũ�� : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->OthersDeed = MyHouseDeed;
		AB_LOG(Warning, TEXT("ģ���� �� ���� ���� �����ϰ� ������ �ڱ� ���� �����մϴ�. ����ũ�� : %d"), FriendsHouseDeed->OthersDeed->Size);
	}

	AB_LOG(Warning, TEXT("�������� ������� ���� ���� ���� �ڵ� ö�ŵ��� �ʽ��ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �ڵ� ö�ŵ��� �ʽ��ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	NewHouseAddress->OthersDeed.Reset();
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �������� ö���߽��ϴ�. ���ּҰ� �����־ �����Դϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);
	AB_LOG(Warning, TEXT("�������� ���� ���� ���� �ڵ� ö�ŵ˴ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);


	// 5�ܰ� ��, �ɷ�ġ �뷱�� �����߿�
	AB_LOG(Warning, TEXT("****** 5�ܰ� ******"));
	NewHouseAddress = new FHouse();
	NewHouseAddress->Size = 300.0f;
	AB_LOG(Warning, TEXT("���� ���������� ���� �����ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);

	NewHouseAddress2 = new FHouse();
	NewHouseAddress2->Size = 350.0f;
	AB_LOG(Warning, TEXT("ģ���� ���� �ٽ� �������ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	{
		TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
		AB_LOG(Warning, TEXT("�� ���� ���� �����մϴ�. ����ũ�� : %d"), MyHouseDeed->Size);
		TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
		AB_LOG(Warning, TEXT("ģ�� ���� ģ���� �����մϴ�. ģ����ũ�� : %d"), FriendsHouseDeed->Size);

		MyHouseDeed->OthersDeed = FriendsHouseDeed;
		AB_LOG(Warning, TEXT("ģ�� ���� ���� �����ϰ� ������ �� ���� �����մϴ�. ģ����ũ�� : %d"), MyHouseDeed->OthersDeed->Size);
		FriendsHouseDeed->AccessHouse = MyHouseDeed;
		AB_LOG(Warning, TEXT("ģ���� �� �� ������ �����մϴ�. ����ũ�� : %d"), FriendsHouseDeed->AccessHouse.Pin()->Size);
	}

	AB_LOG(Warning, TEXT("���� ���� ���� �ڵ� ö�ŵ˴ϴ�. ù��°��ũ�� : %d"), NewHouseAddress->Size);
	AB_LOG(Warning, TEXT("ģ���� ���� ���� �ڵ� ö�ŵ˴ϴ�. �ι�°��ũ�� : %d"), NewHouseAddress2->Size);

	AB_LOG(Warning, TEXT("****** 6�ܰ� ******"));
	WebConnect2 = NewObject<UWebConnection>();
	WebConnect2->Host = TEXT("127.0.0.1");
	//WebConnectionNew->AddToRoot();
	WebConnect2->ConditionalBeginDestroy();
	//GetWorld()->ForceGarbageCollection(true);
	GetWorld()->GetTimerManager().SetTimer(ObjectCheckTimer, this, &UABGameInstance::CheckUObjectAlive, 1.0f, true);


	//UClass* ClassInfo1 = WebConnect->GetClass(); //CDO�� ���� ������ CDO�� UClass���� ������ �����´�, �� ������ ����ؼ� ���� �ڽ��� ������ �����ϴ� ���� ���� ����
	//UClass* ClassInfo2 = UWebConnection::StaticClass(); //�� ��쿡�� ���� �����ϰ� CDO�� ���� ������ UClass�� ����Ŵ

	//if(ClassInfo1 == ClassInfo2)
	//	AB_LOG(Warning, TEXT("ClassInfo1 == ClassInfo2"));

	//for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It) //Ŭ���� ���� ���� ��� �Ӽ��� �˻�
	//{
	//	AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName()); //�Ӽ��� �̸��� �� Ÿ�� ���
	//	UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
	//	if (StrProp) //�Ӽ��� ������ �� �ִٸ�,
	//	{
	//		AB_LOG(Warning, TEXT("Value = %s"), 
	//			*StrProp->GetPropertyValue_InContainer(WebConnect)); //�ش� ������ ���� ������ ��� 
	//			//�������� �� �Ӹ� �ƴ� ���� �־��� ���� ������, �̰��� �⺻ �ν��Ͻ� ������Ʈ�̱� ������ �̸� �����ϴ� ��� ������Ʈ�� ���� ���� ����
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
		AB_LOG(Warning, TEXT("�𸮾������Ʈ�� ���Դϴ�."));
		return;
	}

	if (!WebConnect2->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("�𸮾������Ʈ�� ��ȿ���� �ʽ��ϴ�."));
		return;
	}

	AB_LOG(Warning, TEXT("�𸮾������Ʈ�� ���� ����ֽ��ϴ�. : %s"), *WebConnect2->Host);
}


