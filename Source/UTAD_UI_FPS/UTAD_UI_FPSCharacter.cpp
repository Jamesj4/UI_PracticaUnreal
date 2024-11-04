// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTAD_UI_FPSCharacter.h"
#include "UTAD_UI_FPSProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// UI
#include "TP_WeaponComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/PlayerHUD.h"
#include "UI/SplashWidget.h"
#include "UI/AbilityTree/AbilityTreeHUD.h"

//////////////////////////////////////////////////////////////////////////
// AUTAD_UI_FPSCharacter

AUTAD_UI_FPSCharacter::AUTAD_UI_FPSCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void AUTAD_UI_FPSCharacter::EnablePlayerHud()
{
	
	// Setup Player HUD
	if (PlayerHUDWidget)
	{
	
		PlayerHUDInstance = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHUDWidget);
		PlayerHUDInstance->AddToViewport();
		PlayerHUDInstance->ShowNoWeapon();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player HUD Widget not assigned to UTAD_UI_FPSCharacter"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player HUD Widget not assigned to UTAD_UI_FPSCharacter"));
	}

	SetMaxHealth(MaxHealth);

}

void AUTAD_UI_FPSCharacter::RecreateAbilityTree()
{

	if(AbilityTreeHUD)
	{
		AbilityHudInstance = CreateWidget<UAbilityTreeHUD>(GetWorld(), AbilityTreeHUD);

		//Create all the tree just calling add branch
		for( FAbilityBranchInfo AbilityBranchInfo :AbilityBranches)
		{
			AbilityHudInstance->AddBranch(AbilityBranchInfo);
		}

		AbilityHudInstance->AddToViewport();
		AbilityHudInstance->Show();
	}

	

}

void AUTAD_UI_FPSCharacter::DisableSplashScreen()
{

	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
		EnableInput(PlayerController);
	
	}
	EnablePlayerHud();
}

void AUTAD_UI_FPSCharacter::ToogleAbilityTree()
{
	

	if(!bIsTreeOpen)
	{
		
		PlayerHUDInstance->HideAll();
		
		if(AbilityHudInstance)
		{
			AbilityHudInstance->Show();
		}
		else
		{
			RecreateAbilityTree();
		}

		if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
			PlayerController->bShowMouseCursor = true;

		}

	}
	else
	{
		PlayerHUDInstance->ShowAll();
		AbilityHudInstance->Hide();

		if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
			PlayerController->bShowMouseCursor = false;

		}
	}

	bIsTreeOpen =!bIsTreeOpen;
}

void AUTAD_UI_FPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
	
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	if(SplashHUDWidget)
	{
		SplashHUDInstance = CreateWidget<USplashWidget>(GetWorld(), SplashHUDWidget);
		
		
		// Bind the animation finished event
		FWidgetAnimationDynamicEvent AnimationFinishedEvent;
		AnimationFinishedEvent.BindDynamic(this, &AUTAD_UI_FPSCharacter::DisableSplashScreen);


		SplashHUDInstance->AddToViewport();
		SplashHUDInstance->EnableSplashScreen(AnimationFinishedEvent);

		if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);
			DisableInput(PlayerController);
	
		}
	}
	else
	{
		EnablePlayerHud();
	}

	



}

//////////////////////////////////////////////////////////////////////////// Input

void AUTAD_UI_FPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUTAD_UI_FPSCharacter::Look);

		//Toogle Tree
		EnhancedInputComponent->BindAction(ToogleAbilityTreeAction, ETriggerEvent::Completed, this, &AUTAD_UI_FPSCharacter::ToogleAbilityTree);
	}
}


void AUTAD_UI_FPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUTAD_UI_FPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AUTAD_UI_FPSCharacter::SetHealth(int NewHealth)
{

	if(NewHealth < Health)
	{
		if(OnDamageReceive.IsBound())
		{
			OnDamageReceive.Broadcast();
		}
	}

	
	int ClampedNewHealth = FMath::Clamp(NewHealth, 0, MaxHealth);
	if (ClampedNewHealth != Health)
	{
		Health = ClampedNewHealth;
	}

	// Broadcast the health
	if(OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
}

int AUTAD_UI_FPSCharacter::GetHealth()
{
	return Health;
}

void AUTAD_UI_FPSCharacter::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = FMath::Max(0, NewMaxHealth);

	// Broadcast the health
	if(OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(Health, MaxHealth);
	}
	
}

int AUTAD_UI_FPSCharacter::GetMaxHealth()
{
	return MaxHealth;
}

void AUTAD_UI_FPSCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
	PlayerHUDInstance->ShowAll();
}

bool AUTAD_UI_FPSCharacter::GetHasRifle()
{
	return bHasRifle;
}

void AUTAD_UI_FPSCharacter::SetTotalBullets(int NewTotalBullets)
{
	TotalBullets = NewTotalBullets;

	// Broadcast Ammo changed
	if(AttachedWeaponComponent && OnAmmoCountChanged.IsBound())
	{
		OnAmmoCountChanged.Broadcast(TotalBullets);
	}
}

int AUTAD_UI_FPSCharacter::GetTotalBullets()
{
	return TotalBullets;
}

void AUTAD_UI_FPSCharacter::AddBullets(int Bullets)
{
	TotalBullets += Bullets;

	// Broadcast Ammo changed
	if(AttachedWeaponComponent && OnAmmoCountChanged.IsBound())
	{
		OnAmmoCountChanged.Broadcast(TotalBullets);
	}
	

}

void AUTAD_UI_FPSCharacter::SetAttachedWeaponComponent(UTP_WeaponComponent* WeaponComponent)
{
	AttachedWeaponComponent = WeaponComponent;
}
