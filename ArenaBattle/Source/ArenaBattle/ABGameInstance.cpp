// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance() //������Ʈ ���� �� CDO�� �����ϸ� ȣ�� / ���� ���� ��, CDO�� �����Ͽ� ����
{
	AB_LOG(Warning, TEXT("Constructor Call Start"));

	//�����ڿ��� CDO�� ���� ���� ���Ǵ� ����, �� Ŭ������ CDO�� �� ������ ��� UClass�� ���� ���������
	WebConnect = CreateDefaultSubobject<UWebConnection>(TEXT("WebConnect")); //�� ������ ���� ABGameInstance�� CDO�� WebConnection�� CDO�� �����(�پ����) -> ���� ���� �� CDO�� ������ �� ���� ���� ������

	AB_LOG(Warning, TEXT("Constructor Call End"));
}


void UABGameInstance::Init() //���� ���� �� ���۵�
{
	Super::Init();
	AB_LOG_CALLONLY(Warning);

	WebConnect2 = NewObject<UWebConnection>(this); //

	UClass* ClassInfo1 = WebConnect->GetClass(); //CDO�� ���� ������ CDO�� UClass���� ������ �����´�, �� ������ ����ؼ� ���� �ڽ��� ������ �����ϴ� ���� ���� ����
	UClass* ClassInfo2 = UWebConnection::StaticClass(); //�� ��쿡�� ���� �����ϰ� CDO�� ���� ������ UClass�� ����Ŵ

	if(ClassInfo1 == ClassInfo2)
		AB_LOG(Warning, TEXT("ClassInfo1 == ClassInfo2"));

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

	for (const auto& Entry : ClassInfo1->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
		UFunction* Func1 = ClassInfo1->FindFunctionByName(Entry.Name);
		if (Func1->ParmsSize == 0)
		{
			WebConnect->ProcessEvent(Func1, NULL);
		}
	}
}

