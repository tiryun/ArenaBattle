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
	Super::Init();
	AB_LOG_CALLONLY(Warning);

	WebConnect2 = NewObject<UWebConnection>(this); //this를 넣어줌, this 즉 나에게 소속되게(차일드로) 이 오브젝트를 생성함. 나를 생성시킬 때 나의 부모격 오브젝트는 GetOuter()로 불러올 수 있다.
	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnect2->GetOuter()->GetClass()->GetFullName());

	//GetWorld()를 통해 월드에 배치된 모든 컨텐츠를 검색 가능
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

	//특정 속성의 액터만 추출 가능
	for (TActorIterator<AStaticMeshActor> It(CurrentWorld); It; ++It) //TObjectIterator이렇것도 있어!

	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
	}


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

