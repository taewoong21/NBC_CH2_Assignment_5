// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMyActor.generated.h"

UCLASS()
class CH2_ASSIGNMENT_5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 
	// 캐릭터의 현재 위치를 저장할 변수
	FVector2D CurrentPosition;

	// 총 이동 거리를 저장할 변수
	float TotalDistance;

	// 총 이벤트 발생 횟수를 저장할 변수
	int32 TotalEventCount;

    // (0,0)에서 시작하여 10회 랜덤하게 이동하며 로그를 출력하는 메인 함수
    void Move();
   
    // X 또는 Y 좌표가 이동할 거리를 랜덤하게 반환 (0 또는 1)
    int32 Step();

    // 두 2D 벡터 좌표 사이의 거리를 계산
    float CalculateDistance(const FVector2D& First, const FVector2D& Second);

    // 50% 확률로 이벤트를 발생, 이벤트가 발생하면 1, 아니면 0을 반환
    int32 CreateEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
