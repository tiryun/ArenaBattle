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
	Super::Init();
	AB_LOG_CALLONLY(Warning);

	WebConnect2 = NewObject<UWebConnection>(this); //this�� �־���, this �� ������ �Ҽӵǰ�(���ϵ��) �� ������Ʈ�� ������. ���� ������ų �� ���� �θ�� ������Ʈ�� GetOuter()�� �ҷ��� �� �ִ�.
	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnect2->GetOuter()->GetClass()->GetFullName());

	//GetWorld()�� ���� ���忡 ��ġ�� ��� �������� �˻� ����
	UWorld* CurrentWorld = GetWorld();
	for (const auto& Entry : FActorRange(CurrentWorld))
	{
		AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
		TArray<UObject* > Components;
		Entry->GetDefaultSubobjects(Components);
		for (const auto& CEntry : Components)
		{
			AB_LOG(Warning, TEXT(" -- Component : %s"), *CEntry->GetName());
		}
	}

	//Ư�� �Ӽ��� ���͸� ���� ����
	for (TActorIterator<AStaticMeshActor> It(CurrentWorld); It; ++It) //TObjectIterator�̷��͵� �־�!

	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
	}


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

